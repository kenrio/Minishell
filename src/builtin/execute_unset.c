/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:02:19 by keishii           #+#    #+#             */
/*   Updated: 2025/04/17 02:15:26 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(t_ast *ast, t_envl *envl)
{
	char		*key;

	if (!ast->u_data.cmd.argv[1])
		return (0);
	key = ast->u_data.cmd.argv[1];
	if (envl_rm_node(envl, key))
		return (perror("unset: variable not found"), 1);
	return (0);
}
