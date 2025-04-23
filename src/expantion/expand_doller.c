/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:19:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/23 17:47:40 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*strip_outer_quotes(const char *src);

// we give string, this func() expand string based on appropriate $.
char	*expand_doller(char *str, char **envp, int *status_p)
{
	char			*result;
	char			**elements;
	t_quote_state	quote_state;

	quote_state.in_double_quote = false;
	quote_state.in_single_quote = false;
	elements = boundary_split(str, is_doller);
	if (!elements)
		return (NULL);
	if (update_elements(envp, elements, status_p, &quote_state))
	{
		destroy_split(elements);
		return (NULL);
	}
	result = join_all_split(elements);
	if (!result)
	{
		destroy_split(elements);
		return (NULL);
	}
	destroy_split(elements);
	return (result);
}

// this func() can use in heredoc_expantion.
char	*expand_doller_heredoc(char *str, char **envp, int *status_p)
{
	char			*result;
	char			**elements;
	t_quote_state	quote_state;

	quote_state.in_double_quote = false;
	quote_state.in_single_quote = false;
	elements = boundary_split(str, is_doller);
	if (!elements)
		return (NULL);
	if (update_elements_hdoc(envp, elements, status_p, &quote_state))
	{
		destroy_split(elements);
		return (NULL);
	}
	result = join_all_split(elements);
	if (!result)
	{
		destroy_split(elements);
		return (NULL);
	}
	destroy_split(elements);
	return (result);
}

// echo $USER$USER , $ $? "$USER" , '$USER', $USER!!
// |
// echo tishiahrtishiar , $ 1 "tishihar" , '$USER', tishiahr!!
// this func() can expand doller with removing quote.
char	*dq_expand_doller(char *str, char **envp, int *status_p)
{
	char	*origin;
	char	*result;

	origin = expand_doller(str, envp, status_p);
	if (!origin)
		return (NULL);
	result = strip_outer_quotes(origin);
	free(origin);
	return (result);
}

static char	*strip_outer_quotes(const char *src)
{
	char	*result;
	char	*temp;
	char	quote;

	if (!src)
		return (NULL);
	result = (char *)ft_calloc(ft_strlen(src) + 1, sizeof(char));
	if (!result)
		return (NULL);
	temp = result;
	while (*src)
	{
		if (*src == '\'' || *src == '\"')
		{
			quote = *(src++);
			while (*src && *src != quote)
				*(temp++) = *(src++);
			if (*src == quote)
				src++;
			continue ;
		}
		*(temp++) = *(src++);
	}
	return (result);
}
