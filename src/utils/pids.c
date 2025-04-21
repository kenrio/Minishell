/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pids.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 17:27:01 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/21 21:01:18 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pids(t_pids *pids)
{
	pids->head = NULL;
	pids->tail = NULL;
}

int	pids_push_back(t_pids *pids, pid_t pid)
{
	t_pid_node	*new;

	if (!pids)
		return (1);
	new = (t_pid_node *) malloc(sizeof(t_pid_node));
	if (!new)
		return (1);
	new->pid = pid;
	new->next = NULL;
	if (!pids->head)
	{
		pids->head = new;
		pids->tail = new;
	}
	else
	{
		pids->tail->next = new;
		pids->tail = new;
	}
	return (0);
}

void	wait_pids(t_pids *pids, int *status)
{
	t_pid_node	*curr;
	t_pid_node	*next;

	curr = pids->head;
	while (curr)
	{
		if (curr->pid == -1)
		{
			curr = curr->next;
			continue ;
		}
		next = curr->next;
		if (curr->next == NULL)
		{
			if (waitpid(curr->pid, status, 0) == -1)
			{
				if (errno == EINTR)
					continue ;
				break ;
			}
			if (WIFEXITED(*status))
				*status = WEXITSTATUS(*status);
			else if (WIFSIGNALED(*status))
				*status = 128 + WTERMSIG(*status);
		}
		else
			waitpid(curr->pid, NULL, 0);
		curr = next;
	}
}

void	destroy_pids(t_pids	*pids)
{
	t_pid_node	*curr;
	t_pid_node	*next;

	curr = pids->head;
	while (curr)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
	pids->head = NULL;
	pids->tail = NULL;
}
