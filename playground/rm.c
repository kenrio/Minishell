#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	int	i;

	if (argc < 2)
	{
		fprintf(stderr, "%s: no arguments\n", argv[0]);
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		if ((unlink(argv[i]) < 0))
		{
			perror(argv[i]);
			exit(1);
		}
		i++;
	}
	exit(0);
}