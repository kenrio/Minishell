/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:19:27 by keishii           #+#    #+#             */
/*   Updated: 2025/03/15 15:28:37 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_quoted_token(char *line,
				t_token_array *array, t_token_state *state);
static void	count_non_quoted_token(char *line,
				t_token_array *array, t_token_state *state);

int	count_tokens(char *line, t_token_array *array)
{
	t_token_state	state;

	init_token_state(&state);
	array->len = 0;
	while (line[state.current_index])
	{
		if ((line[state.current_index] == '\'' && !state.in_dquote)
			|| (line[state.current_index] == '"' && !state.in_squote))
			count_quoted_token(line, array, &state);
		else if (!state.in_squote && !state.in_dquote)
			count_non_quoted_token(line, array, &state);
		state.current_index++;
	}
	return (array->len);
}

static void	count_quoted_token(char *line,
	t_token_array *array, t_token_state *state)
{
	if (!state->new_token)
	{
		state->new_token = true;
		array->len++;
	}
	toggle_quote_state(line, state);
	if (line[state->current_index + 1]
		&& !ft_isspace(line[state->current_index + 1])
		&& !is_operator(line[state->current_index + 1]))
		state->new_token = true;
}

static void	count_non_quoted_token(char *line,
	t_token_array *array, t_token_state *state)
{
	if (ft_isspace(line[state->current_index]))
		state->new_token = false;
	else if (is_operator(line[state->current_index]))
	{
		state->new_token = false;
		array->len++;
		if (is_double_operator(line, state->current_index))
			state->current_index++;
	}
	else if (!state->new_token)
	{
		state->new_token = true;
		array->len++;
	}
}
