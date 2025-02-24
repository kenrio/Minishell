/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:08:21 by keishii           #+#    #+#             */
/*   Updated: 2025/02/24 17:17:50 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	main_loop(char *input_line, t_token_list *token_list);
static char	*get_input_line(void);

int	main(int argc, char **argv, char **envp)
{
	char			*input_line;
	t_token_list	token_list;

	(void)argc;
	(void)argv;
	(void)envp;
	input_line = NULL;
	main_loop(input_line, &token_list);
	exit(0);
}

static void	main_loop(char *input_line, t_token_list *token_list)
{
	while (1)
	{
		input_line = get_input_line();
		if (!input_line)
			break ;
		lexer(input_line, token_list);
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
