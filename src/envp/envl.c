/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:57:20 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/28 12:58:48 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	init_envl(t_envl *lst);
static	int	envl_push_back(t_envl *lst, char *value);

// envl: node->node->node->NULL
// node.value = "USER=tishihar" etc..
// use malloc.
// lst, node, value.
t_envl	*make_envl(char **envp)
{
	t_envl	*result;

	result = (t_envl *) ft_calloc(1, sizeof(t_envl));
	init_envl(result);
	while (*envp)
	{
		envl_push_back(result, ft_strdup(*envp));
		envp++;
	}
	return (result);
}

void	destroy_envl(t_envl *lst)
{
	t_env_node	*curr;
	t_env_node	*next;

	if (!lst)
		return ;
	curr = lst->head;
	while (curr)
	{
		next = curr->next;
		free(curr->value);
		free(curr);
		curr = next;
	}
	free(lst);
}

static	int	envl_push_back(t_envl *lst, char *value)
{
	t_env_node	*new;

	if (!lst)
		return (1);
	new = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	if (!new)
		return (1);
	new->value = value;
	new->next = NULL;
	if (lst->count == 0)
	{
		lst->head = new;
		lst->tail = new;
	}
	else
	{
		lst->tail->next = new;
		lst->tail = new;		
	}
	lst->count += 1;
	return (0);
}

static	void	init_envl(t_envl *lst)
{
	lst->count = 0;
	lst->head = NULL;
	lst->tail = NULL;
}
