/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:36:38 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/19 14:04:30 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_expand_line(char **envp, char *str);
static char	*create_expand_exit_line(int exit_status, char *str);
static void	update_quote_state(char *e, t_quote_state *quote_state);
static int	handle_update(char **e, char **envp, int *stp, t_quote_state *q_st);

// if you can find appropriate doller,
// this func() expand doller in if　statement.
// Only go into an if statement when it should be expand doller. 
// argument: envp->env_pointer, elements->show expand_doller.c,
// stp->exit_status_pointer, q_st->quote_state
int	update_elements_hdoc(char **envp, char **e, int *stp, t_quote_state *q_st)
{
	while (*e)
	{
		if (handle_update(e, envp, stp, q_st))
			return (1);
		update_quote_state(*e, q_st);
		e++;
	}
	return (0);
}

// expand_elemet($USER akfdj -> tishihar akfdj)
static char	*create_expand_line(char **envp, char *str)
{
	char	*start;
	char	*env_key;
	char	*result;

	start = ++str;
	while (*str && is_env_char(*str))
		str++;
	env_key = ft_substr(start, 0, str - start);
	if (!env_key)
		return (NULL);
	result = ft_strjoin(get_env_value_bykey(envp, env_key), str);
	free(env_key);
	return (result);
}

// $? -> 0 etc...
static char	*create_expand_exit_line(int exit_status, char *str)
{
	char	*status_str;
	char	*result;

	status_str = ft_itoa(exit_status);
	if (!status_str)
		return (NULL);
	result = ft_strjoin(status_str, str + 2);
	free(status_str);
	return (result);
}

// e -> elements
static void	update_quote_state(char *e, t_quote_state *quote_state)
{
	bool	*in_double;
	bool	*in_single;

	in_double = &quote_state->in_double_quote;
	in_single = &quote_state->in_single_quote;
	while (*e)
	{
		if (*e == '\"')
			*in_double = !(*in_double);
		else if (*e == '\'')
			*in_single = !(*in_single);
		e++;
	}
}

//arguments:
// e -> elements, envp -> env_pointer,
// stp -> exit_status_pointer, q_st -> quote_state
static int	handle_update(char **e, char **envp, int *stp, t_quote_state *q_st)
{
	char	*temp;

	(void) q_st;
	if (is_doller(**e) && (*(*e + 1) == '?'))
	{
		temp = *e;
		*e = create_expand_exit_line(*stp, *e);
		if (!(*e))
			return (1);
		free(temp);
	}
	else if (
		is_doller(**e)
		&& is_env_char(*(*e + 1))
	)
	{
		temp = *e;
		*e = create_expand_line(envp, *e);
		if (!(*e))
			return (1);
		free(temp);
	}
	return (0);
}
