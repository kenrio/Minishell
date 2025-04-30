/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 20:57:20 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/29 11:52:56 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envl(t_envl *lst);

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
		if (envl_push_back(result, *envp) != 0)
		{
			destroy_envl(result);
			return(NULL);
		}
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

// this function allocate value to heap_memory;
int	envl_push_back(t_envl *lst, char *value)
{
	t_env_node	*new;

	if (!lst)
		return (1);
	new = (t_env_node *)ft_calloc(1, sizeof(t_env_node));
	if (!new)
		return (1);
	new->value = ft_strdup(value);
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

t_envl *envl_clone(const t_envl *src)
{
	t_env_node	*curr;
	t_envl		*cpy;

	cpy = (t_envl *)ft_calloc(1, sizeof(t_envl));
	if (!cpy)
		return (NULL);
	init_envl(cpy);
	curr = src->head;
	while (curr)
	{
		if (envl_push_back(cpy, curr->value) != 0)
			return(destroy_envl(cpy), NULL);
		curr = curr->next;
	}
	return (cpy);
}

static void	init_envl(t_envl *lst)
{
	lst->count = 0;
	lst->head = NULL;
	lst->tail = NULL;
}
