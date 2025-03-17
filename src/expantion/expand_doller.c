/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:19:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/17 16:38:02 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static	char	*join_all_split(char **array);
static	void	update_quote_state(char *e, bool *in_single, bool *in_double);
static	int		update_elements(char **envp, char **elements, bool*in_single, bool *in_double);
static	char	*create_expand_line(char **envp, char *str);

// we give string, this func() expand string based on appropriate $.
char	*expand_doller(char **envp, char *str)
{
	char	*result;
	char	**elements;
	bool	in_double_quote;
	bool	in_single_quote;

	in_double_quote = false;
	in_single_quote = false;
	elements = boundary_split(str, is_doller);
	if (!elements)
		return (NULL);
	if (update_elements(envp, elements, &in_single_quote, &in_double_quote))
		return (NULL);
	result = join_all_split(elements);
	if (!result)
		return (NULL);
	destroy_split(elements);
	return (result);
}

static	void	update_quote_state(char *e, bool *in_single, bool *in_double)
{
	while (*e)
	{
		if (*e == '\"')
			*in_double = !(*in_double);
		else if (*e == '\'')
			*in_single = !(*in_single);
		e++;
	}
}

static	char	*join_all_split(char **array)
{
	char	*result;
	char	*temp;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*array)
	{
		temp = result;
		result = ft_strjoin(result, *array);
		if (!result)
			return (NULL);
		free(temp);
		array++;
	}
	return (result);
}

// if you can find appropriate doller, this func() expand doller in if　statement.
// Only go into an if statement when it should be expand doller. 
static	int	update_elements(char **envp, char **elements, bool *in_single, bool *in_double)
{
	char	*temp;

	while (*elements)// &? 
	{
		// ?として展開する必要がある。
		if (is_doller(**elements) && (*(*elements + 1) == '?'))
		{
			temp = *elements;
			*elements = ft_strjoin("EXIT_STATUS", *elements + 2);
			if (!(*elements))
				return (1);
			free(temp);
		}
		else if (is_doller(**elements) && is_env_char(*(*elements + 1)) && (!(*in_single) || *in_double))
		{
			temp = *elements; //$USER akfdj
			*elements = create_expand_line(envp, *elements);// tishihar akfdjに上書きされる
			if (!(*elements))
				return (1);
			free(temp);
		}
		update_quote_state(*elements, in_single, in_double);
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
