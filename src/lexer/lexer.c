/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:01:33 by keishii           #+#    #+#             */
/*   Updated: 2025/03/03 05:00:00 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	count_tokens(char *line, t_token_list *list);
static void	init_token_state(t_token_state *state);
static void	handle_quote(char *line, t_token_state *state);
static int	is_operator(char c);
static int	is_double_operator(char *line, int index);
static int	tokenize(char *line, t_token_list *list);
static int	add_token(char *line, t_token_list *list, t_token_state *state);

int	lexer(char *input_line, int *exit_status)
{
	t_token_list	token_list;
	t_token_state	check_state;

	// printf("input_line: %s\n", input_line);
	token_list.token_list = NULL;
	token_list.num = 0;
	count_tokens(input_line, &token_list);
	init_token_state(&check_state);
	while (input_line[check_state.current_index])
	{
		handle_quote(input_line, &check_state);
		check_state.current_index++;
	}
	if (check_state.in_squote || check_state.in_dquote)
	{
		*exit_status = 1;
		return (*exit_status);
	}
	if (token_list.num == 0)
	{
		*exit_status = 0;
		return (*exit_status);
	}
	token_list.token_list
		= (t_token *)malloc(sizeof(t_token) * (token_list.num + 1));
	if (!token_list.token_list)
	{
		*exit_status = 1;
		return (*exit_status);
	}
	*exit_status = tokenize(input_line, &token_list);
	// *exit_status = lexer_split(input_line, &token_list);
	printf("\ntoken_list->num: %d\n", token_list.num);
	printf("\n");
	for (int i = 0; i < token_list.num; i++)
	{
		printf("token_list[%d]: %s\n", i, token_list.token_list[i].token);
	}
	return (*exit_status);
}

static void	count_tokens(char *line, t_token_list *list)
{
	t_token_state	state;

	init_token_state(&state);
	list->num = 0;
	while (line[state.current_index])
	{
		if ((line[state.current_index] == '\'' && !state.in_dquote)
			|| (line[state.current_index] == '"' && !state.in_squote))
		{
			if (!state.new_token)
			{
				state.new_token = true;
				list->num++;
			}
			handle_quote(line, &state);
		}
		else if (!state.in_squote && !state.in_dquote)
		{
			if (ft_isspace(line[state.current_index]))
				state.new_token = false;
			else if (is_operator(line[state.current_index]))
			{
				state.new_token = false;
				list->num++;
				if (is_double_operator(line, state.current_index))
					state.current_index++;
			}
			else if (!state.new_token)
			{
				state.new_token = true;
				list->num++;
			}
		}
		state.current_index++;
	}
}

static void	init_token_state(t_token_state *state)
{
	state->in_squote = false;
	state->in_dquote = false;
	state->new_token = false;
	state->start_index = 0;
	state->current_index = 0;
	state->token_index = 0;
}

static void	handle_quote(char *line, t_token_state *state)
{
	if (line[state->current_index] == '\'' && !state->in_dquote)
		state->in_squote = !state->in_squote;
	else if (line[state->current_index] == '"' && !state->in_squote)
		state->in_dquote = !state->in_dquote;
}

static int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}
static int	is_double_operator(char *line, int index)
{
	return ((line[index] == '>' && line[index + 1] == '>')
			|| (line[index] == '<' && line[index + 1] == '<'));
}

static int	tokenize(char *line, t_token_list *list)
{
	t_token_state	state;

	init_token_state(&state);
	while (line[state.current_index])
	{
		if ((line[state.current_index] == '\'' && !state.in_dquote)
			|| (line[state.current_index] == '"' && !state.in_squote))
		{
			if (!state.in_squote && !state.in_dquote && state.new_token)
			{
				state.start_index = state.current_index;
				state.new_token = false;
			}
			handle_quote(line, &state);
			if ((line[state.current_index] == '\''
				|| line[state.current_index] == '"')
				&& !state.in_squote && !state.in_dquote)
			{
				state.current_index++;
				add_token(line, list, &state);
				state.new_token = true;
				state.start_index = state.current_index;
				continue ;
			}
		}
		else if (!state.in_squote && !state.in_dquote)
		{
			if (ft_isspace(line[state.current_index]))
			{
				if (!state.new_token)
				{
					add_token(line, list, &state);
					state.new_token = true;
				}
				state.start_index = state.current_index + 1;
			}
			else if (is_operator(line[state.current_index]))
			{
				if (!state.new_token)
					add_token(line, list, &state);
				state.start_index = state.current_index;
				if (is_double_operator(line, state.current_index))
					state.current_index++;
				state.current_index++;
				add_token(line, list, &state);
				state.new_token = true;
				state.start_index = state.current_index;
				continue ;
			}
			else if (state.new_token)
			{
				state.start_index = state.current_index;
				state.new_token = false;
			}
		}
		state.current_index++;
	}
	if (!state.new_token)
		add_token(line, list, &state);
	return (0);
}

static int	add_token(char *line, t_token_list *list, t_token_state *state)
{
	int	len;

	len = state->current_index - state->start_index;
	if (len <= 0)
		return (0);
	list->token_list[state->token_index].token
		= (char *)malloc(sizeof(char) * (len + 1));
	if (!list->token_list[state->token_index].token)
		return (1);
	ft_strlcpy(list->token_list[state->token_index].token,
			&line[state->start_index], len + 1);
	list->token_list[state->token_index].token[len] = '\0';
	state->token_index++;
	return (0);
}
