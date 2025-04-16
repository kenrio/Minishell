/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:41:22 by keishii           #+#    #+#             */
/*   Updated: 2025/04/17 01:54:04 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_export(t_ast *ast, t_envl *envl)
{
	(void)ast;
	t_env_node	*curr;

	curr = envl->head;
	while (curr)
	{
		printf("declare -x %s\n", curr->value);
		curr = curr->next;
	}
	return (0);
}
