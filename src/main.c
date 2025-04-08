/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:08:21 by keishii           #+#    #+#             */
/*   Updated: 2025/04/08 12:28:39 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	main_loop(char *input_line, t_envl *envl, int *exit_status);
static char	*get_input_line(int *exit_status);

volatile sig_atomic_t	g_signal;

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	char	*input_line;
	t_envl	*envl;

	(void)argc;
	(void)argv;
	input_line = NULL;
	envl = make_envl(envp);
	exit_status = main_loop(input_line, envl, &exit_status);
	exit(exit_status);
}

static int	main_loop(char *input_line, t_envl *envl, int *exit_status)
{
	t_ast			*ast_node;
	t_token_array	token_array;

	while (1)
	{
		input_line = get_input_line(exit_status);
		if (!input_line)
			break ;
		*exit_status = 0;
		*exit_status = lexer(&token_array, input_line, exit_status);
		if (token_array.len == 0 || *exit_status == 1)
		{
			free_token_array(&token_array);
			continue ;
		}
		parser(&ast_node, &token_array, envl, exit_status);
		free_token_array(&token_array);
		run_ast(ast_node, exit_status);
		free_ast(ast_node);
	}
	return (*exit_status);
}

static char	*get_input_line(int *exit_status)
{
	char	*input_line;

	g_signal = 0;
	set_idle_handler();
	input_line = readline(PROMPT);
	if (g_signal == 0 && input_line && ft_strlen(input_line) > 0)
		add_history(input_line);
	if (g_signal == SIGINT)
	{
		free(input_line);
		*exit_status = 130;
	}
	return (input_line);
}
