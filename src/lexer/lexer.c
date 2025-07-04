/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:01:33 by keishii           #+#    #+#             */
/*   Updated: 2025/04/19 13:51:27 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_opened_quotes(char *line, int *exit_status);

int	lexer(t_token_array *array, char *input_line, int *exit_status)
{
	t_token_array	*token_array;

	token_array = array;
	(*token_array).tokens = NULL;
	(*token_array).len = 0;
	if (count_tokens(input_line, &(*token_array)) == 0)
		return (1);
	if (check_opened_quotes(input_line, exit_status))
		return (*exit_status = 2, 1);
	(*token_array).tokens
		= (t_token *)ft_calloc((*token_array).len + 1, sizeof(t_token));
	if (!(*token_array).tokens)
	{
		perror("ft_callloc");
		return (1);
	}
	if (tokenize(input_line, &(*token_array), exit_status))
	{
		free_token_array(&(*token_array));
		return (1);
	}
	assign_token_type(&(*token_array));
	free(input_line);
	return (0);
}

static int	check_opened_quotes(char *line, int *exit_status)
{
	t_token_state	check_state;

	init_token_state(&check_state);
	while (line[check_state.current_index])
	{
		toggle_quote_state(line, &check_state);
		check_state.current_index++;
	}
	if (check_state.in_squote || check_state.in_dquote)
	{
		if (check_state.in_squote)
			perror("syntax error: looking for matching \'");
		else
			perror("syntax error: looking for matching \"");
		*exit_status = 1;
		return (1);
	}
	return (0);
}
