/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:08:21 by keishii           #+#    #+#             */
/*   Updated: 2025/04/21 21:06:35 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	main_loop(char *input_line, t_envl *envl,
				int *exit_status, int *lexer_status);
static char	*get_input_line(int *exit_status);
static int	event(void);

volatile sig_atomic_t	g_signal;

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	int		lexer_status;
	char	*input_line;
	t_envl	*envl;

	(void)argc;
	(void)argv;
	input_line = NULL;
	exit_status = 0;
	lexer_status = 0;
	envl = make_envl(envp);
	exit_status = main_loop(input_line, envl, &exit_status, &lexer_status);
	destroy_envl(envl);
	exit(exit_status);
}

static int	main_loop(char *input_line, t_envl *envl,
				int *exit_status, int *lexer_status)
{
	t_ast			*ast_node;
	t_token_array	token_array;

	while (1)
	{
		// printf("initial: exit_status: %d\n", *exit_status);
		input_line = get_input_line(exit_status);
		if (g_signal != 0)
			continue ;
		if (!input_line)
			break ;
		*lexer_status = 0;
		lexer(&token_array, input_line, lexer_status);
		if (token_array.len == 0 || *lexer_status == 2)
		{
			if (token_array.len != 0)
				*exit_status = *lexer_status;
			free_token_array(&token_array);
			continue ;
		}
		parser(&ast_node, &token_array, envl, exit_status);
		// printf("parser: exit_status: %d\n", *exit_status);
		free_token_array(&token_array);
		run_ast(ast_node, envl, exit_status);
		free_ast(ast_node);
	}
	return (*exit_status);
}

static int	event(void)
{
	return (0);
}

static char	*get_input_line(int *exit_status)
{
	char	*input_line;

	g_signal = 0;
	rl_event_hook = event;
	set_idle_handler();
	printf("DEBUG exit_status before readline: %d\n", *exit_status);
	input_line = readline(PROMPT);
	printf("DEBUG exit_status after readline: %d\n", *exit_status);
	if (g_signal == 0 && input_line && ft_strlen(input_line) > 0)
		add_history(input_line);
	if (g_signal == SIGINT)
	{
		free(input_line);
		*exit_status = 128 + SIGINT;
	}
	if (!input_line)
		write(STDOUT_FILENO, "exit\n", 5);
	return (input_line);
}
