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

struct  cmd {
    int		argc;
    char	**argv;
    int 	capa;
    int     status;
    int     pid;
    struct  cmd *next;
};

#define REDIRECT_P(cmd) ((cmd)->argc == -1)
#define PID_BUILTIN -2
#define BUILTIN_P(cmd) ((cmd)->pid == PID_BUILTIN)

struct  buildin {
    char    *name;
    void    (*f)(int argc, char *argv[]);
};

static void             prompt(void);
static int              invoke_commands(struct cmd *cmd);
static void             exec_pipeline(struct cmd *cmd);
static void             redirect_stdout(char *path);
static int              wait_pipeline(struct cmd *cmdhead);
static struct cmd       *pipeline_tail(struct cmd *cmd_head);
static struct cmd       *parse_command_line(char *cmdline);
static void             free_cmd(struct cmd *p);
static struct builtin   *lookup_builtin(char *name);
static int              builtin_cd(int argc, char *argv[]);
static int              builtin_pwd(int argc, char *argv[]);
static int              builtin_exit(int argc, char *argv[]);
static void             *xmalloc(size_t size);
static void             *xrealloc(void *ptr, size_t size);

static char *program_name;

int main(int argc, char *argv[])
{
    program_name = argv[0];         // 実行ファイル名をprogram_nameに代入
    for (;;)                        // 無限ループ
        prompt();                   // 
    exit(0);                        // プログラムを正常終了
}

#define LINEBUF_MAX 2048

static void prompt(void)
{
    static char buf[LINEBUF_MAX];                                   // 文字の配列bufを宣言
    struct cmd  *cmd;                                               // cmd構造体を宣言

    fprintf(stdout, "$ ");                                          // "$ "（プロンプト）を標準出力に出力
    fflush(stdout);                                                 // プロンプトが即座に出力されるように、標準出力をフラッシュ
    if (fgets(buf, LINEBUF_MAX, stdin) == NULL)                     // 「LINEBUF_MAX - 1」分のデータを標準入力から読み取り、bufにセットしbufへのポインタを返す
        exit(0);                                                    // fgets()が失敗し、返り血がNULLの場合、プログラムを終了
    cmd = parse_command_line(buf);                                  // 
    if (cmd == NULL)
    {
        fprintf(stderr, "%s: syntax error\n", program_name);
        return ;
    }
    if (cmd->argc > 0)
        invoke_commands(cmd);
    free_cmd(cmd);
}

#define INIT_ARGV 8
#define IDENT_CHAR_P(c) (!isspace((int)c) && ((c) != '|') && ((c) != '>'))

static struct cmd*  parse_command_line(char *p)
{
    struct cmd  *cmd;

    cmd = xamlloc(sizeof(struct cmd));
    cmd->argc = 0;
    cmd->argv = xmalloc(sizeof(char *) * INIT_ARGV);
    cmd->capa = INIT_ARGV;
    cmd->next = NULL;
    while (*p)
    {
        while (*p && isspace((int)*p))
            *p++ = '\0';
        if (! IDENT_CHAR_P(*p))
            break ;
        if (*p && IDENT_CHAR_P(*p))
        {
            if (cmd->capa <= cmd->argc)
            {
                cmd->capa *= 2;
                cmd->argv = xrealloc(cmd->argv, cmd->capa);
            }
            cmd->argv[cmd->argc] = p;
            cmd->argc++;
        }
        while (*p && IDENT_CHAR_P(*p))
            p++;
    }
    if (cmd->capa <= cmd->argc)
    {
        cmd->capa += 1;
        cmd->argv =  xrealloc(cmd->argv, cmd->capa);
    }
    cmd->argv[cmd->argc] = NULL;
    if (*p == '|' || *p == '>')
    {
        if (cmd == NULL || cmd->argc == 0) goto parse_error;
        cmd->next = parse_command_line(p + 1);
        if (cmd->next == NULL || cmd->next->argc == 0) goto parse_error;
        if (*p == '>')
        {
            if (cmd->next->argc != 1) goto parse_error;
            cmd->next->argc = -1;
        }
        *p = '\0';
    }
    return (cmd);

    parse_error:
        if (cmd) free_cmd(cmd);
        return (NULL);
}
