/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 14:47:04 by keishii           #+#    #+#             */
/*   Updated: 2025/01/19 15:19:16 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 2048

static void	do_cat(const char *path);
static void	die(const char *s);

int	main(int argc, char *argv[])
{
	int	i;

	if (argc < 2)
	{
		fprintf(stderr, "%s: file name not given\n", argv[0]);
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		do_cat(argv[i]);
		i++;
	}
	exit(0);
}

static void	do_cat(const char *path)
{
	int				fd;
	unsigned char	buf[BUFFER_SIZE];
	int				n;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		die(path);
	while (1)
	{
		n = read(fd, buf, sizeof buf);
		if (n < 0)
			die(path);
		if (n == 0)
			break ;
		if (write(STDOUT_FILENO, buf, n) < 0)
			die(path);
	}
	if (close(fd) < 0)
		die(path);
}

static void	die(const char *s)
{
	perror(s);
	exit(1);
}
