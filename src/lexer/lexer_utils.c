/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:45:55 by keishii           #+#    #+#             */
/*   Updated: 2025/03/05 21:57:10 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token_state(t_token_state *state)
{
	state->in_squote = false;
	state->in_dquote = false;
	state->new_token = false;
	state->start_index = 0;
	state->current_index = 0;
	state->token_index = 0;
}

void	handle_quote(char *line, t_token_state *state)
{
	if (line[state->current_index] == '\'' && !state->in_dquote)
		state->in_squote = !state->in_squote;
	else if (line[state->current_index] == '"' && !state->in_squote)
		state->in_dquote = !state->in_dquote;
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
int	is_double_operator(char *line, int index)
{
	return ((line[index] == '>' && line[index + 1] == '>')
			|| (line[index] == '<' && line[index + 1] == '<'));
}
