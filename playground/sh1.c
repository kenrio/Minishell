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

struct cmd {
	char	**argv;
	int		argc;
	long	capa;
};

static void		invoke_cmd(struct cmd *cmd);
static struct	cmd *read_cmd(void);
static struct	cmd *parse_cmd(char	*cmdline);
static void		free_cmd(struct cmd	*p);
static void		*xmalloc(size_t size);
static void		*xrealloc(void *ptr, size_t size);

static char	*program_name;

# define PROMPT	"minishell$ "

int	main(int argc, char *argv[])
{
	(void)argc;

	program_name = argv[0];				// 実行ファイル名をprogram_nameに代入
	for (;;)							// 無限ループ
	{
		struct cmd	*cmd;				// cmd構造体へのポインタcmdを宣言

		fprintf(stdout, PROMPT);		// PROMPTを標準出力に出力
		fflush(stdout);					// PROMPTが即座に出力されるようにバッファをフラッシュ
		cmd = read_cmd();				// ユーザの入力コマンドを取得
		if (cmd->argc > 0)				// argcメンバが0より大きい場合（トークン（単語）が1つ以上の場合）
			invoke_cmd(cmd);			// コマンドを実行
		free_cmd(cmd);					// 確保したメモリを開放
	}
	exit(0);							// プログラムを終了、終了ステータスは0
}

static void invoke_cmd(struct cmd *cmd)
{
	pid_t	pid;											// プロセスIDを格納する変数を宣言

	pid = fork();											// 現在のプロセスを複製し、新しい子プロセスを作成、その返り値をpidに代入
	if (pid < 0)											// forkの失敗時（pidが0未満の場合）
	{
		perror("fork");										// 標準エラーに"fork"を出力
		exit(1);											// プログラムを終了
	}
	if (pid > 0)											// 親プロセスの場合（pidが0より大きい場合）
		waitpid(pid, NULL, 0);								// 子プロセスの終了を待つ
	else													// 子プロセスの場合（pidが0の場合）
	{
		// execvpでcmd->argv[0]（コマンド名）を実行、
		// argvはexecvpに渡すための引数リスト（NULL終端の配列）
		execvp(cmd->argv[0], cmd->argv);					// コマンドの実行が成功した子プロセスはそのまま終了
		fprintf(stderr, "%s: command not found: %s\n",		// execvpが失敗した場合、標準エラーにエラーメッセージを出力
			program_name, cmd->argv[0]);
		exit(1);											// プログラムを終了
	}
}

#define LINE_BUF_SIZE 2048

static struct cmd *read_cmd(void)
{
	static char	buf[LINE_BUF_SIZE];							// charの配列を宣言

	if ((fgets(buf, LINE_BUF_SIZE, stdin) == NULL))			// 「LINE_BUF_SIZE - 1」分を標準入力からデータを読み取り、bufににセットしbufへのポインタを返す
		exit(0);											// fgetsが失敗し、返り値がNULLの場合、プログラムを終了
	return (parse_cmd(buf));								// ユーザ入力のコマンド文字列bufを解析し、各トークンをargv[]に格納したcmd構造体に返す
}

# define INIT_CAPA 16

static struct cmd *parse_cmd(char *cmdline)
{
	char		*p;											// charへのポインタpを宣言
	struct cmd	*cmd;										// cmd構造体へのポインタcmdを宣言

	p = cmdline;											// cmdlineの先頭アドレスをpに代入
	cmd = xmalloc(sizeof(struct cmd));						// cmd用のメモリをxmallocで確保し、その先頭アドレスをcmdに代入
	cmd->argc = 0;											// cmd構造体のargcメンバに0を代入
	cmd->argv = xmalloc(sizeof(char *) * INIT_CAPA);		// cmd構造体のargvメンバ用のメモリをxmallocで確保し、その先頭アドレスをargvメンバに代入
	cmd->capa = INIT_CAPA;									// cmd構造体のcapaメンバにINIT_CAPAを代入
	while (*p)												// pが指す文字がヌル文字（'\0'）でない限り
	{
		while (*p && isspace((int)*p))						// pが指す文字がヌル文字（'\0'）でなく、空白文字（スペース、タブ、改行など）の場合
			*p++ = '\0';									// pが指す文字にヌル文字（'\0'）にし、ポインタを次の位置に進める
		if (*p)												// pが指す文字がヌル文字（'\0'）でない場合
		{
			if (cmd->capa <= cmd->argc + 1)					// capaメンバがargcメンバ + 1以下の場合
			{
				cmd->capa *= 2;								// capaメンバを2倍にする
				cmd->argv = xrealloc(cmd->argv, cmd->capa);	// argvメンバ用のメモリサイズをxreallocで変更し、その先頭アドレスをargvメンバに代入
			}
			cmd->argv[cmd->argc] = p;						// argvメンバのargc番目（初期値は0）の要素にpを代入
			cmd->argc++;									// argcをインクリメント
		}
		while (*p && !isspace((int)*p))						// pが指す文字がヌル文字（'\0'）でなく、空白文字以外の場合
			p++;											// ポインタを次の位置に進める
	}
	cmd->argv[cmd->argc] = NULL;							// argvメンバのargc番目の要素にNULLを代入
	return (cmd);											// cmd構造体を返す
}

static void free_cmd(struct cmd *cmd)
{
	free(cmd->argv);				// cmd構造体のargvメンバのメモリを解放
	free(cmd);						// cmd構造体のメモリを解放
}

static void *xmalloc(size_t size)
{
	void	*p;							// voidへのポインタpを宣言

	p = malloc(size);					// mallocでsize分のメモリ領域をポインタpに割り当て
	if (!p)								// mallocが失敗し、pがNULLの場合
	{
		perror("malloc");				// 標準エラーに"malloc"を出力
		exit(1);						// プログラムを終了
	}
	return (p);							// 確保されたメモリ領域のアドレスを返す
}

static void *xrealloc(void *ptr, size_t size)
{
	void	*p;							// voidへのポインタpを宣言

	if (!ptr)							// ptrがNULLの場合（新規に宣言されたポインタの場合）
		return (xmalloc(size));			// xmallocでsize分のメモリを確保し、ポインタを返す
	p = realloc(ptr, size);				// ptrが指すメモリのサイズを変更し、新しい領域のアドレスをpにセット
	if (!p)								// reallocが失敗し、pがNULLの場合
	{
		perror("realloc");				// 標準エラーに"realloc"を出力
		exit(1);						// プログラムを終了
	}
	return (p);							// 確保・変更されたメモリ領域のアドレスを返す
}
