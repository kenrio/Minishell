/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:38:15 by keishii           #+#    #+#             */
/*   Updated: 2025/03/05 21:43:57 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_quoted_token(char *line, t_token_state *state);
static int	handle_delimiter(char *line,
		t_token_list *list, t_token_state *state);
static int	handle_space_delimiter(char *line,
		t_token_list *list, t_token_state *state);
static int	handle_operator(char *line,
		t_token_list *list, t_token_state *state);

int	tokenize(char *line, t_token_list *list)
{
	t_token_state	state;

	init_token_state(&state);
	while (line[state.current_index])
	{
		if ((line[state.current_index] == '\'' && !state.in_dquote)
			|| (line[state.current_index] == '"' && !state.in_squote))
			handle_quoted_token(line, &state);
		else if (!state.in_squote && !state.in_dquote)
			if (handle_delimiter(line, list, &state) == 1)
				continue ;
		state.current_index++;
	}
	if (!state.new_token)
		add_token(line, list, &state);
	return (0);
}

static void	handle_quoted_token(char *line, t_token_state *state)
{
	if (!state->in_squote && !state->in_dquote && state->new_token)
	{
		state->start_index = state->current_index;
		state->new_token = false;
	}
	handle_quote(line, state);
	if (line[state->current_index + 1]
		&& (!is_operator(line[state->current_index + 1])))
		state->new_token = false;
}

static int	handle_delimiter(char *line,
		t_token_list *list, t_token_state *state)
{
	if (ft_isspace(line[state->current_index]))
		return (handle_space_delimiter(line, list, state));
	else if (is_operator(line[state->current_index]))
		return (handle_operator(line, list, state));
	else if (state->new_token)
	{
		state->start_index = state->current_index;
		state->new_token = false;
	}
	return (0);
}

static int	handle_space_delimiter(char *line,
	t_token_list *list, t_token_state *state)
{
	if (!state->new_token)
	{
		add_token(line, list, state);
		state->new_token = true;
	}
	state->start_index = state->current_index + 1;
	return (0);
}

static int	handle_operator(char *line,
	t_token_list *list, t_token_state *state)
{
	if (!state->new_token)
		add_token(line, list, state);
	state->start_index = state->current_index;
	if (is_double_operator(line, state->current_index))
		state->current_index++;
	state->current_index++;
	add_token(line, list, state);
	state->new_token = true;
	state->start_index = state->current_index;
	return (1);
}
