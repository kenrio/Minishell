/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:08:21 by keishii           #+#    #+#             */
/*   Updated: 2025/03/18 18:15:53 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	main_loop(char *input_line, int *exit_status);
static char	*get_input_line(void);

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	char	*input_line;

	(void)argc;
	(void)argv;
	(void)envp;
	input_line = NULL;
	exit_status = main_loop(input_line, &exit_status);
	exit(exit_status);
}

static int	main_loop(char *input_line, int *exit_status)
{
	t_token_array	token_array;

	while (1)
	{
		input_line = get_input_line();
		if (!input_line)
			break ;
		*exit_status = 0;
		*exit_status = lexer(&token_array, input_line, exit_status);
		*exit_status = parser(&token_array, exit_status);
		printf("\nexit_status: %d\n\n", *exit_status);
	}
	return (*exit_status);
}

static char	*get_input_line(void)
{
	char	*input_line;

	input_line = readline(PROMPT);
	if (input_line && ft_strlen(input_line) > 0)
		add_history(input_line);
	return (input_line);
}
