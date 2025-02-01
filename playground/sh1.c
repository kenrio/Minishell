#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
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
	program_name = argv[0];				// 実行ファイル名をprogram_nameに代入
	for (;;)							// 無限ループ
	{
		struct cmd	*cmd;				// cmd構造体へのポインタcmdを宣言

		fprintf(stdout, PROMPT);		// PROMPTを標準出力に出力
		fflush(stdout);					// PROMPTが即座に出力されるようにバッファをフラッシュ
		cmd = read_cmd();				// 
		if (cmd->argc > 0)
			invoke_cmd(cmd);
		free_cmd(cmd);
	}
	exit(0);
}

#define LINE_BUF_SIZE 2048

static struct cmd *read_cmd(void)
{
	static char	buf[LINE_BUF_SIZE];							// charの固定長配列を宣言

	if ((fgets(buf, LINE_BUF_SIZE, stdin) == NULL))			// 「LINE_BUF_SIZE - 1」分を標準入力からデータを読み取り、bufににセットしbufへのポインタを返す
		exit(0);											// fgetsが失敗し、返り値がNULLの場合はプログラムを終了する
	return (parse_cmd(buf));								// 
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
	while (*p)
	{
		while (*p && isspace((int)*p))
			*p++ = '\0';
		if (*p)
		{
			if (cmd->capa <= cmd->argc + 1)
			{
				cmd->capa *= 2;
				cmd->argv = xrealloc(cmd->argv, cmd->capa);
			}
			cmd->argv[cmd->argc] = p;
			cmd->argc++;
		}
		while (*p && !isspace((int)*p))
			p++;
	}
	cmd->argv[cmd->argc] = NULL;
	return (cmd);
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
	return (p);							// ポインタpを返す
}

static void *xrealloc(void *ptr, size_t size)
{
	void	*p;

	if (!ptr)
		return (xmalloc(size));
	p = realloc(ptr, size);
	if (!p)
	{
		perror("realloc");
		exit(1);
	}
	return (p);
}
