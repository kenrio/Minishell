/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:38:15 by keishii           #+#    #+#             */
/*   Updated: 2025/03/14 13:38:35 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	start_quoted_token(char *line, t_token_state *state);
static int	handle_non_quoted_token(char *line, t_token_list *list,
				t_token_state *state, int *exit_status);
static int	end_token_at_space(char *line, t_token_list *list,
				t_token_state *state, int *exit_status);
static int	extract_operator_token(char *line, t_token_list *list,
				t_token_state *state, int *exit_status);

int	tokenize(char *line, t_token_list *list, int *exit_status)
{
	t_token_state	state;

	init_token_state(&state);
	while (line[state.current_index])
	{
		if ((line[state.current_index] == '\'' && !state.in_dquote)
			|| (line[state.current_index] == '"' && !state.in_squote))
			start_quoted_token(line, &state);
		else if (!state.in_squote && !state.in_dquote)
		{
			if (handle_non_quoted_token(line, list, &state, exit_status) == -1)
				continue ;
			else if (*exit_status == 1)
				return (1);
		}
		state.current_index++;
	}
	if (state.new_token)
		if (add_token(line, list, &state, exit_status))
			return (1);
	return (0);
}

static void	start_quoted_token(char *line, t_token_state *state)
{
	if (!state->in_squote && !state->in_dquote && !state->new_token)
	{
		state->start_index = state->current_index;
		state->new_token = true;
	}
	handle_quote(line, state);
	if (line[state->current_index + 1]
		&& (!ft_isspace(line[state->current_index + 1]))
		&& (!is_operator(line[state->current_index + 1])))
		state->new_token = true;
}

static int	handle_non_quoted_token(char *line,
		t_token_list *list, t_token_state *state, int *exit_status)
{
	if (ft_isspace(line[state->current_index]))
		return (end_token_at_space(line, list, state, exit_status));
	else if (is_operator(line[state->current_index]))
		return (extract_operator_token(line, list, state, exit_status));
	else if (!state->new_token)
	{
		state->start_index = state->current_index;
		state->new_token = true;
	}
	return (0);
}

static int	end_token_at_space(char *line,
	t_token_list *list, t_token_state *state, int *exit_status)
{
	if (state->new_token)
	{
		if (add_token(line, list, state, exit_status))
			return (1);
		state->new_token = false;
	}
	state->start_index = state->current_index + 1;
	return (0);
}

static int	extract_operator_token(char *line,
	t_token_list *list, t_token_state *state, int *exit_status)
{
	if (state->new_token)
		if (add_token(line, list, state, exit_status))
			return (1);
	state->start_index = state->current_index;
	if (is_double_operator(line, state->current_index))
		state->current_index++;
	state->current_index++;
	if (add_token(line, list, state, exit_status))
		return (1);
	state->new_token = false;
	state->start_index = state->current_index;
	return (-1);
}
