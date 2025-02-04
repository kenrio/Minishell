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

struct	buildin {
	char	*name;
	void	(*f)(int argc, char *argv[]);
};

static void				prompt(void);
static int				invoke_commands(struct cmd *cmd);
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
	cmd = parse_command_line(buf);									// 
	if (cmd == NULL)												// cmdがNULLの場合
	{
		fprintf(stderr, "%s: syntax error\n", program_name);		// 標準エラーにエラーメッセージを出力
		return ;													// 関数を終了
	}
	if (cmd->argc > 0)												// argcメンバが0よりも大きい場合
		invoke_commands(cmd);										// 
	free_cmd(cmd);													// 確保したメモリを解放
}

static void	invoke_cmd(struct cmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(1);
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
	else
	{
		execvp(cmd->argv[0], cmd->argv);
		fprintf(stderr, "%s: command not found: %s\n", program_name, cmd->argv[0]);
		exit(1);
	}
}

#define INIT_ARGV 8
#define IDENT_CHAR_P(c) (!isspace((int)c) && ((c) != '|') && ((c) != '>'))

static struct cmd*  parse_command_line(char *p)
{
	struct cmd	*cmd;														// cmd構造体へのポインタcmdを宣言

	cmd = xamlloc(sizeof(struct cmd));										// cmd用のメモリをxmallocで確保し、その先頭アドレスをcmdに代入
	cmd->argc = 0;															// argcメンバに0を代入
	cmd->argv = xmalloc(sizeof(char *) * INIT_ARGV);						// argvメンバ用のメモリをxmallocで確保し、その先頭アドレスをargvに代入
	cmd->capa = INIT_ARGV;													// capaメンバにINIT_CAPAを代入
	cmd->next = NULL;														// nextメンバにNULLを代入
	while (*p)																// pが指す文字がヌル文字（'\0'）でない限り
	{
		while (*p && isspace((int)*p))										// pが指す文字がヌル文字（'\0'）でなく、空白文字（スペース、タブ、改行など）の場合
			*p++ = '\0';													// pが指す文字をヌル文字（'\0'）にし、ポインタを次の位置に進める
		if (! IDENT_CHAR_P(*p))												// pが指す文字が空白文字またはパイプ記号またはリダイレクト記号の場合
			break ;															// whileループを抜ける
		if (*p && IDENT_CHAR_P(*p))											// pが指す文字がヌル文字（'\0'）でも、空白文字でも、パイプ記号でも、リダイレクト記号でない場合
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
	free(cmd->argv);		// cmd構造体のargvメンバのメモリを解放
	free(cmd);				// cmd構造体のメモリを解放
}
