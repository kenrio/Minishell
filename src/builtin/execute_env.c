/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:21:57 by keishii           #+#    #+#             */
/*   Updated: 2025/04/16 22:39:01 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_ast *ast)
{
	int		i;

	i = 0;
	while (ast->u_data.cmd.envp[i])
		printf("%s\n", ast->u_data.cmd.envp[i++]);
	return (0);
}
