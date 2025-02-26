/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:08:21 by keishii           #+#    #+#             */
/*   Updated: 2025/02/26 18:42:56 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	main_loop(char *input_line);
static char	*get_input_line(void);

int	main(int argc, char **argv, char **envp)
{
	char	*input_line;

	(void)argc;
	(void)argv;
	(void)envp;
	input_line = NULL;
	main_loop(input_line);
	exit(0);
}

static void	main_loop(char *input_line)
{
	while (1)
	{
		input_line = get_input_line();
		if (!input_line)
			break ;
		lexer(input_line);
		free(input_line);
	}
}

static char	*get_input_line(void)
{
	char	*input_line;

	input_line = readline(PROMPT);
	if (input_line && ft_strlen(input_line) > 0)
		add_history(input_line);
	return (input_line);
}
