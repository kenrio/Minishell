/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_doller.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:19:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/18 14:07:12 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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
