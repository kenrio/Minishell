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

# define PROMPT	"prompt$ "
# define LINE_BUF_SIZE	2048

static char	*read_cmd(void);

struct cmd {
	int argc;
	char **argv;
	int capa;
};

int	main(int argc, char *argv[])
{
	char *program_name;
	char *buf;
	
	program_name = argv[0];
	printf("program_name: %s\n", program_name);
	while (1)
	{
		// struct cmd	*cmd;
		fprintf(stdout, "%s", PROMPT);
		fflush(stdout);
		buf = read_cmd();
		printf("main buf: %s\n", buf);
		if (argc > 0)
		{
			printf("execute command\n");
			exit(0);
		}
	}
	exit(0);
}

static char	*read_cmd(void)
{
	static char	buf[LINE_BUF_SIZE];

	if (read(1, buf, sizeof buf) < 0)
		exit(0);
	printf("read_cmd buf: %s\n", buf);
	return (buf);
}
