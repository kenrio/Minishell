/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:19:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/14 17:46:22 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static	char	*join_all_split(char **array);
static	void	update_quote_state(char *e, int *in_single, int *in_double);
static	int		*update_elements(char **envp, char **elements, char *in_single, char *in_double);
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

static	void	update_quote_state(char *e, int *in_single, int *in_double)
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

static	int	*update_elements(char **envp, char **elements, char *in_single, char *in_double)
{
	char	*temp;

	while (*elements)
	{
		if (is_doller(**elements) && (!(*in_single) || *in_double))
		{
			temp = *elements; //$USER akfdj
			*elements = create_expand_line(envp, *elements);// tishihar akfdjに上書きされる
			if (!(*elements))
				return (1);
			free(temp);
		}
		update_quote_state(*elements, in_double, in_single);
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
	while (*str && (ft_isalpha(*str) || (*str == '_')))
		str++;
	
	// この時点でスペースに今はいるはず
	env_key = ft_substr(start, 0, str - start);// USER
	if (!env_key)
		return (NULL);
	result = ft_strjoin(get_env_value_bykey(envp, env_key), str);
	free(env_key);
	return (result);
}
