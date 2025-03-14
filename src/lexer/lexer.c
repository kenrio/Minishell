/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:01:33 by keishii           #+#    #+#             */
/*   Updated: 2025/03/14 14:03:50 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_opened_quotes(char *line, int *exit_status);

int	lexer(char *input_line, int *exit_status)
{
	t_token_list	token_list;

	token_list.token_list = NULL;
	token_list.num = 0;
	if (check_opened_quotes(input_line, exit_status))
		return (*exit_status);
	if (count_tokens(input_line, &token_list) == 0)
		return (*exit_status);
	token_list.token_list
		= (t_token *)ft_calloc(token_list.num + 1, sizeof(t_token));
	if (!token_list.token_list)
	{
		perror("ft_callloc");
		return (1);
	}
	if (tokenize(input_line, &token_list, exit_status))
	{
		free_token_list(&token_list);
		return (1);
	}
	assign_token_type(&token_list);
	free(input_line);
	return (*exit_status);
}

static int	check_opened_quotes(char *line, int *exit_status)
{
	t_token_state	check_state;

	init_token_state(&check_state);
	while (line[check_state.current_index])
	{
		handle_quote(line, &check_state);
		check_state.current_index++;
	}
	if (check_state.in_squote || check_state.in_dquote)
	{
		if (check_state.in_squote)
			perror("minishell$: syntax error: looking for matching \'");
		else
			perror("minishell$: syntax error: looking for matching \"");
		*exit_status = 1;
		return (1);
	}
	return (0);
}
