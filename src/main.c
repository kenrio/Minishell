/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:08:21 by keishii           #+#    #+#             */
/*   Updated: 2025/02/01 20:10:54 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	char		*program_name;
	char		*buf;
	pid_t		pid;
	extern char	**environ;

	(void)argc;
	program_name = argv[0];
	printf("program_name: %s\n", program_name);
	while ((buf = readline(PROMPT)))
	{
		if (ft_strlen(buf) > 0)
			add_history(buf);
		pid = fork();
		if (pid > 0)
			waitpid(pid, NULL, 0);
		else if (pid == 0)
		{
			printf("buf: %s\n", buf);
			execve("/bin/ls", argv, environ);
			exit(1);
		}
		else
			exit(1);
	}
	free(buf);
	exit(0);
}
