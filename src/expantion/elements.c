/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 17:59:47 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/18 13:23:52 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*create_expand_line(char **envp, char *str);
static	char	*create_expand_exit_line(int exit_status, char *str);
static	void	update_quote_state(char *e, t_quote_state *quote_state);
static	int		handle_update(char	**elements, char **envp, int *status_p, t_quote_state *quote_state);


// if you can find appropriate doller, this func() expand doller in if　statement.
// Only go into an if statement when it should be expand doller. 
int	update_elements(char **envp, char **elements, int *status_p, t_quote_state *quote_state)
{
	while (*elements)
	{
		if (handle_update(elements, envp, status_p, quote_state))
			return (1);
		update_quote_state(*elements, quote_state);
		elements++;
	}
	return (0);
}

// expand_elemet($USER akfdj -> tishihar akfdj)
static	char	*create_expand_line(char **envp, char *str)
{
	char	*start;
	char	*env_key;
	char	*result;

	start = ++str;
	while (*str && is_env_char(*str))
		str++;
	
	// この時点でスペースに今はいるはず
	env_key = ft_substr(start, 0, str - start);// USER
	if (!env_key)
		return (NULL);
	result = ft_strjoin(get_env_value_bykey(envp, env_key), str);
	free(env_key);
	return (result);
}

static	char	*create_expand_exit_line(int exit_status, char *str)
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

static	void	update_quote_state(char *e, t_quote_state *quote_state)
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

static	int		handle_update(char	**elements, char **envp, int *status_p, t_quote_state *quote_state)
{
	char	*temp;

	if (is_doller(**elements)&& (*(*elements + 1) == '?'))
	{
		temp = *elements;
		*elements = create_expand_exit_line(*status_p, *elements);
		if (!(*elements))
			return (1);
		free(temp);
	}
	else if (
		is_doller(**elements)
		&& is_env_char(*(*elements + 1))
		&& (!(quote_state->in_single_quote) || quote_state->in_double_quote)
	)
	{
		temp = *elements;
		*elements = create_expand_line(envp, *elements);
		if (!(*elements))
			return (1);
		free(temp);
	}
	return (0);
}
