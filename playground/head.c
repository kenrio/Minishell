#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

static void	do_head(FILE *f, long nlines);

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
	{"lines", required_argument, NULL, 'n'},
	{"help", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

int	main(int argc, char *argv[])
{
	int		opt;
	long	nlines;
	int		i;
	FILE	*f;

	nlines = DEFAULT_N_LINES;
	while ((opt = getopt_long(argc, argv, "n", longopts, NULL)) != -1)
	{
		if (opt == 'n')
		{
			nlines = atol(optarg);
			break ;
		}
		else if (opt == 'h')
		{
			fprintf(stdout, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
			exit(0);
		}
		else if (opt == '?')
		{
			fprintf(stderr, "Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
			exit(1);
		}
	}
	if (optind == argc)
		do_head(stdin, nlines);
	else
	{
		i = optind;
		while (i < argc)
		{
			f = fopen(argv[i], "r");
			if (!f)
			{
				perror(argv[i]);
				exit(1);
			}
			do_head(f, nlines);
			fclose(f);
			i++;
		}
	}
	exit(0);
}

static void	do_head(FILE *f, long nlines)
{
	int	c;

	if (nlines <= 0)
			return ;
	while ((c = getc(f)) != EOF)
	{
		if (putchar(c) < 0)
				exit(1);
		if (c == '\n')
		{
			nlines--;
			if (nlines == 0)
					return ;
		}
	}
}
