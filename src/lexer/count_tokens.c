/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:19:27 by keishii           #+#    #+#             */
/*   Updated: 2025/03/12 16:36:42 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_quoted_token(char *line,
				t_token_list *list, t_token_state *state);
static void	count_non_quoted_token(char *line,
				t_token_list *list, t_token_state *state);

int	count_tokens(char *line, t_token_list *list)
{
	t_token_state	state;

	init_token_state(&state);
	list->num = 0;
	while (line[state.current_index])
	{
		if ((line[state.current_index] == '\'' && !state.in_dquote)
			|| (line[state.current_index] == '"' && !state.in_squote))
			count_quoted_token(line, list, &state);
		else if (!state.in_squote && !state.in_dquote)
			count_non_quoted_token(line, list, &state);
		state.current_index++;
	}
	return (list->num);
}

static void	count_quoted_token(char *line,
	t_token_list *list, t_token_state *state)
{
	if (!state->new_token)
	{
		state->new_token = true;
		list->num++;
	}
	handle_quote(line, state);
	if (line[state->current_index + 1]
		&& !ft_isspace(line[state->current_index + 1])
		&& !is_operator(line[state->current_index + 1]))
		state->new_token = true;
}

static void	count_non_quoted_token(char *line,
	t_token_list *list, t_token_state *state)
{
	if (ft_isspace(line[state->current_index]))
		state->new_token = false;
	else if (is_operator(line[state->current_index]))
	{
		state->new_token = false;
		list->num++;
		if (is_double_operator(line, state->current_index))
			state->current_index++;
	}
	else if (!state->new_token)
	{
		state->new_token = true;
		list->num++;
	}
}
