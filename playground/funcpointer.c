#include <stdio.h>

int	plus1(int n)
{
	return (n + 1);
}

int	main(void)
{
	int	(*f)(int);
	int	result;

	f = plus1;
	result = f(5);
	printf("%d\n", result);
	return (0);
}
