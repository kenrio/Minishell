/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 02:02:19 by keishii           #+#    #+#             */
/*   Updated: 2025/04/18 19:42:59 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_unset(t_ast *ast, t_envl *envl)
{
	char	*key;
	int		i;	

	if (!ast->u_data.cmd.argv[1])
		return (1);
	i = 1;
	while (ast->u_data.cmd.argv[i])
	{
		key = ast->u_data.cmd.argv[i];
		if (envl_rm_node(envl, key))
			return (1);
		i++;
	}
	return (0);
}
