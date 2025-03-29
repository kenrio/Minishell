/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:57:11 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/28 12:49:10 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	destroy_all(char **origin, char **curr);

char	**make_envp_by_envl(t_envl *lst)
{
	t_env_node	*curr;
	char		**result;
	char		**tmp;

	result = (char **) ft_calloc(lst->count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	tmp = result;
	curr = lst->head;
	while (curr)
	{
		*tmp = ft_strdup(curr->value);
		if (*tmp == NULL)
		{
			destroy_all(result, tmp);
			return (NULL);
		}
		tmp++;
		curr = curr->next;
	}
	return (result);
}

static	void	destroy_all(char **origin, char **curr)
{
	while (origin <= curr)
	{
		free(*curr);
		curr--;
	}
	free(origin);
}
