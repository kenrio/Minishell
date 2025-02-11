#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

struct	cmd {
	int		argc;
	char	**argv;
	int		capa;
	int		status;
	int		pid;
	struct	cmd *next;
};

#define REDIRECT_P(cmd) ((cmd)->argc == -1)
#define PID_BUILTIN -2
#define BUILTIN_P(cmd) ((cmd)->pid == PID_BUILTIN)

struct	builtin {
	char	*name;
	int		(*f)(int argc, char *argv[]);
};

static void				prompt(void);
static int				invoke_commands(struct cmd *cmdhead);
static void				exec_pipeline(struct cmd *cmd);
static void				redirect_stdout(char *path);
static int				wait_pipeline(struct cmd *cmdhead);
static struct cmd		*pipeline_tail(struct cmd *cmd_head);
static struct cmd		*parse_command_line(char *cmdline);
static void				free_cmd(struct cmd *p);
static struct builtin	*lookup_builtin(char *name);
static int				builtin_cd(int argc, char *argv[]);
static int				builtin_pwd(int argc, char *argv[]);
static int				builtin_exit(int argc, char *argv[]);
static void				*xmalloc(size_t size);
static void				*xrealloc(void *ptr, size_t size);

static char	*program_name;

int main(int argc, char *argv[])
{
	(void)argc;
	program_name = argv[0];			// 実行ファイル名をprogram_nameに代入
	for (;;)						// 無限ループ
		prompt();					// 
	exit(0);						// プログラムを正常終了
}

#define LINEBUF_MAX 2048

static void prompt(void)
{
	static char	buf[LINEBUF_MAX];									// 文字の配列bufを宣言
	struct cmd	*cmd;												// cmd構造体を宣言

	fprintf(stdout, "$ ");											// "$ "（プロンプト）を標準出力に出力
	fflush(stdout);													// プロンプトが即座に出力されるように、標準出力をフラッシュ
	if (fgets(buf, LINEBUF_MAX, stdin) == NULL)						// 「LINEBUF_MAX - 1」分のデータを標準入力から読み取り、bufにセットしbufへのポインタを返す
		exit(0);													// fgets()が失敗し、返り血がNULLの場合、プログラムを終了

	cmd = parse_command_line(buf);									// コマンドラインを解析し、パイプorリダイレクトで区切られた各コマンドをcmd構造体のリストとして管理
																	// 各コマンドの引数はargv[]に格納し、NULL終端の配列として扱う									

	if (cmd == NULL)												// cmdがNULLの場合
	{
		fprintf(stderr, "%s: syntax error\n", program_name);		// 標準エラーにエラーメッセージを出力
		return ;													// 関数を終了
	}
	if (cmd->argc > 0)												// argcメンバが0よりも大きい場合
		invoke_commands(cmd);										// 
	free_cmd(cmd);													// 確保したメモリを解放
}

static int	invoke_commands(struct cmd *cmdhead)
{
	int	st;															// int型の変数stを宣言
	int	original_stdin = dup(0);									// 標準入力のfdを複製してoriginal_stdinに代入
	int	original_stdout = dup(1);									// 標準出力のfdを複製してoriginal_stdoutに代入

	exec_pipeline(cmdhead);
	st = wait_pipeline(cmdhead);
	close(0); dup2(original_stdin, 0); close(original_stdin);
	close(1); dup2(original_stdout, 1); close(original_stdout);

	return (st);
}

#define HEAD_P(cmd) ((cmd) == cmdhead)
#define TAIL_P(cmd) (((cmd)->next == NULL) || REDIRECT_P((cmd)->next))

static void	exec_pipeline(struct cmd *cmdhead)
{
	struct cmd	*cmd;													// cmd構造体を宣言
	int			fds1[2] = {-1, -1};										// int[2]型の配列fds1（パイプ用のfd）を宣言、-1で初期化
	int			fds2[2] = {-1, -1};										// int[2]型の配列fds2（パイプ用のfd）を宣言、-1で初期化

	for (cmd = cmdhead; cmd && !REDIRECT_P(cmd); cmd = cmd->next)		// cmdをcmdheadの先頭に設定し、cmdがNULLでなくcmd->argcが-1でない限りループを続ける
	{																	// （リダイレクトまたは最後のコマンドまで処理したらループを終了）
		fds1[0] = fds2[0];												// fds1[0]にfds2[0]を代入（最後に作成した入力用パイプを引き継ぐ）
		fds1[1] = fds2[1];												// fds1[1]にfds2[1]を代入（最後に作成した出力用パイプを引き継ぐ）
		if (!TAIL_P(cmd))												// cmdがリストの最後のコマンドでないかつ、次のコマンドがリダイレクトでない場合
		{
			if (pipe(fds2) < 0)											// pipe(2)でfds[1]からfds[0]へのストリームを作成、pipe(2)の返り値が0未満の場合
			{
				perror("pipe");											// 標準エラーにエラーメッセージを出力
				exit(3);												// プログラムを異常終了
			}
		}
		if (lookup_builtin(cmd->argv[0]) != NULL)						// ビルトインコマンドリストの中から、入力されたコマンドに該当するものを検索する。該当するものがある場合
			cmd->pid = PID_BUILTIN;										// pidメンバにPID_BUILTIN（-2）を代入
		else															// ビルトインコマンドリストの中に、入力されたコマンドに該当するものがない場合
		{
			cmd->pid = fork();											// 現在のプロセスを複製し、新しい子プロセスを作成、その返り値をpidに代入
			if (cmd->pid < 0)											// forkの失敗時（pidが0未満の場合）
			{
				perror("fork");											// 標準エラーにエラーメッセージを出力
				exit(3);												// プログラムを異常終了
			}
			if (cmd->pid > 0)											// 親プロセスの場合（pidが0より大きい）
			{
				if (fds1[0] != -1) close(fds1[0]);						// fds1[0]が-1以外の場合、fds1[0]をcloseする
				if (fds1[1] != -1) close(fds1[1]);						// fds1[1]が-1以外の場合、fds1[1]をcloseする
				continue ;												// 以降の処理をスキップし、次のコマンドへ処理を進める
			}
		}
		if (!HEAD_P(cmd))												// cmdが先頭のコマンドでない場合
		{
			close(0); dup2(fds1[0], 0); close(fds1[0]);					// 	stdinをcloseする、fds1[0]をstdinに複製する、fds1[0]をcloseする
			close(fds1[1]);												// fds1[1]をcloseする
		}
		if (!TAIL_P(cmd))												// cmdがリストの最後のコマンドでないかつ、次のコマンドがリダイレクトでない場合
		{
			close(fds2[0]);												// fds[0]をcloseする
			close(1); dup2(fds2[1], 1); close(fds2[1]);					// 1をcloseする、fds2[1]を1に複製する、fds2[1]をcloseする
		}
		if ((cmd->next != NULL) && REDIRECT_P(cmd->next))				// cmdがリストの最後のノードないかつ、リダイレクトの場合
			redirect_stdout(cmd->next->argv[0]);						// 
		if (!BUILTIN_P(cmd))											// コマンドがビルトインコマンド以外のコマンドの場合
		{
			execvp(cmd->argv[0], cmd->argv);							// execvp(3)を使って、cmd->argv[0]（コマンド名）を実行
			fprintf(stderr, "%s: command not found: %s\n",				// exexvpが失敗した場合、標準エラーにエラーメッセージを出力
				program_name, cmd->argv[0]);
			exit(1);													// プログラムを終了
		}
	}
}

static void	redirect_stdout(char *path)
{
	int	fd;

	close(1);
	fd = open(path, O_WRONLY|O_TRUNC|O_CREAT, 0666);
	if (fd < 0)
	{
		perror(path);
		return;
	}
	if (fd != 1)
	{
		dup2(fd, 1);
		close(fd);
	}
}

static int	wait_pipeline(struct cmd *cmdhead)
{
	struct cmd	*cmd;

	for (cmd = cmdhead; cmd && !REDIRECT_P(cmd); cmd = cmd->next)
	{
		if (BUILTIN_P(cmd))
			cmd->status = lookup_builtin(cmd->argv[0])->f(cmd->argc, cmd->argv);
		else
			waitpid(cmd->pid, &cmd->status, 0);
	}
	return (pipeline_tail(cmdhead)->status);
}

static struct cmd	*pipeline_tail(struct cmd *cmdhead)
{
	struct cmd	*cmd;

	for (cmd = cmdhead; !TAIL_P(cmd); cmd = cmd->next)
		;
	return (cmd);
}

#define INIT_ARGV 8
#define IDENT_CHAR_P(c) (!isspace((int)c) && ((c) != '|') && ((c) != '>'))

static struct cmd*  parse_command_line(char *p)
{
	struct cmd	*cmd;														// cmd構造体へのポインタcmdを宣言

	cmd = xmalloc(sizeof(struct cmd));										// cmd用のメモリをxmallocで確保し、その先頭アドレスをcmdに代入
	cmd->argc = 0;															// argcメンバに0を代入
	cmd->argv = xmalloc(sizeof(char *) * INIT_ARGV);						// argvメンバ用のメモリをxmallocで確保し、その先頭アドレスをargvに代入
	cmd->capa = INIT_ARGV;													// capaメンバにINIT_CAPAを代入
	cmd->next = NULL;														// nextメンバにNULLを代入
	while (*p)																// pが指す文字がヌル文字（'\0'）でない限り
	{
		while (*p && isspace((int)*p))										// pが指す文字がヌル文字（'\0'）でなく、空白文字（スペース、タブ、改行など）の限り
			*p++ = '\0';													// pが指す文字をヌル文字（'\0'）にし、ポインタを次の位置に進める
		if (! IDENT_CHAR_P(*p))												// pが指す文字が空白文字またはパイプ記号またはリダイレクト記号の場合
			break ;															// whileループを抜ける
		if (*p && IDENT_CHAR_P(*p))											// pが指す文字がヌル文字（'\0'）でも、空白文字でも、パイプ記号でも、リダイレクト記号でもない場合
		{
			if (cmd->capa <= cmd->argc)										// capaメンバがargc + 1以下の場合
			{
				cmd->capa *= 2;												// capaメンバの値を2倍にする
				cmd->argv = xrealloc(cmd->argv, cmd->capa);					// argvメンバ用のメモリサイズをxreallocで変更し、その先頭アドレスをargvメンバに代入
			}
			cmd->argv[cmd->argc] = p;										// argvメンバのargc番目（初期値は0）の要素にpを代入
			cmd->argc++;													// argcをインクリメント
		}
		while (*p && IDENT_CHAR_P(*p))										// pが指す文字がヌル文字（'\0'） でも、空白文字でも、パイプ記号でも、リダイレクト記号でもない限り
			p++;															// ポインタを次の位置に進める
	}
	if (cmd->capa <= cmd->argc)												// capaメンバがargc以下の場合
	{
		cmd->capa += 1;														// capaメンバに1を加算
		cmd->argv =  xrealloc(cmd->argv, cmd->capa);						// argvメンバ用のメモリサイズをxreallocで変更し、その先頭アドレスをargvメンバに代入
	}
	cmd->argv[cmd->argc] = NULL;											// argvメンバのargc番目の要素にNULLを代入
	if (*p == '|' || *p == '>')												// pが指す文字がパイプ記号または、リダイレクト記号の場合
	{
		if (cmd == NULL || cmd->argc == 0) goto parse_error;				// cmdがNULLまたは、argcメンバが0の場合、parse_errorラベルにジャンプ
		cmd->next = parse_command_line(p + 1);								// nextメンバに次のトークン（pポインタの次の位置）を解析
		if (cmd->next == NULL || cmd->next->argc == 0) goto parse_error;	// nextメンバがNULLの場合、nextメンバのargcメンバが0の場合、parse_errorラベルにジャンプ
		if (*p == '>')														// pが指す文字がリダイレクト記号の場合
		{
			if (cmd->next->argc != 1) goto parse_error;						// nextメンバのargcメンバが1でない場合、parse_errorラベルにジャンプ
			cmd->next->argc = -1;											// nextメンバのargcメンバに-1を代入
		}
		*p = '\0';															// pが指す文字にヌル文字（'\0'）を代入
	}
	return (cmd);															// cmd構造体を返す

	parse_error:															// parse_errorラベル
		if (cmd) free_cmd(cmd);												// cmd構造体がNULLでない場合、確保したメモリを解放
		return (NULL);														// NULLを返す
}

static void	free_cmd(struct cmd *cmd)
{
	if (cmd->next != NULL)
		free_cmd(cmd->next);
	free(cmd->argv);			// cmd構造体のargvメンバのメモリを解放
	free(cmd);					// cmd構造体のメモリを解放
}

struct builtin	builtins_list[] = {
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"exit", builtin_exit},
	{NULL, NULL}
};

static struct builtin	*lookup_builtin(char *cmd)
{
	struct builtin	*p;							// builtin構造体へのポインタpを宣言

	for (p = builtins_list; p->name; p++)		// pをbuiltin_listの先頭に設定し、リストのnameがNULLに到達するまでループを続ける（NULLはリストの終端）
	{
		if (strcmp(cmd, p->name) == 0)			// strcmp(3)を使ってcmdとp->nameを比較し、一致（strcmp(cmd, p->name) == 0）した場合、
			return (p);							// ビルトインコマンドと判断してpを返す
	}
	return (NULL);								// ビルトインコマンドに該当するものがなければ、NULLを返す
}

static int	builtin_cd(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "%s: wrong argument\n", argv[0]);
		return (1);
	}
	if (chdir(argv[1]) < 0)
	{
		perror(argv[1]);
		return (1);
	}
	return (0);
}

static int	builtin_pwd(int argc, char *argv[])
{
	char	buf[LINEBUF_MAX];

	if (argc != 1)
	{
		fprintf(stderr, "%s: wrong argument\n", argv[0]);
		return (1);
	}
	if (!getcwd(buf, LINEBUF_MAX))
	{
		fprintf(stderr, "%s: cannot get working directory\n", argv[0]);
		return (1);
	}
	printf("%s\n", buf);
	return (0);
}

static int	builtin_exit(int argc, char *argv[])
{
	if (argc != 1)
	{
		fprintf(stderr, "%s: too many arguments\n", argv[0]);
		return (1);
	}
	exit(0);
}

static void	*xmalloc(size_t size)
{
	void	*p;

	p = calloc(1, size);
	if (!p)
		exit(3);
	return (p);
}

static void	*xrealloc(void *ptr, size_t size)
{
	void	*p;

	if (!ptr) return (xmalloc(size));
	p = realloc(ptr, size);
	if (!p)
		exit(3);
	return (p);
}
