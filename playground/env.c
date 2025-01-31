#include <stdio.h>
#include <stdlib.h>

extern char	**environ;

int	main(void)
{
	char	**p;

	p = environ;
	while (*p)
	{
		printf("%s\n", *p);
		p++;
	}
	exit(0);
}
