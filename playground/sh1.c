#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>

# define PROMPT	"minishell$ "
# define LINE_BUF_SIZE	2048

// static void	invoke_cmd(void);

struct cmd {
	int argc;
	char **argv;
	int capa;
};

int	main(int argc, char *argv[])
{
	char		*program_name;
	char		*buf;
	pid_t		pid;
	extern char	**environ;

	(void)argc;
	program_name = argv[0];
	printf("program_name: %s\n", program_name);
	while (1)
	{
		buf = readline(PROMPT);
		if (!buf)
			exit(1);
		pid = fork();
		if (pid > 0)
			waitpid(pid, NULL, 0);
		else if (pid == 0)
		{
			if (*buf)
			{
				printf("buf: %s\n", buf);
				execve("/bin/ls", argv, environ);
			}
			exit(1);
		}
		else
			exit(1);
	}
	free(buf);
	exit(0);
}
