/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:59:48 by keishii           #+#    #+#             */
/*   Updated: 2025/04/18 20:33:03 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(t_ast *ast)
{
	char	cwd[4096];
	char	*arg;

	if (!(getcwd(cwd, sizeof(cwd))))
		return (*(ast->u_data.cmd.stp) = 1, 1);
	if (ast->u_data.cmd.argv[1])
	{
		arg = ast->u_data.cmd.argv[1];
		if ((arg[0] == '-' && ft_strcmp(arg, "-") != 0)
			&& ft_strcmp(arg, "--") != 0)
		{
			ft_putstr_fd("pwd: option not accepted\n", STDERR_FILENO);
			return (*(ast->u_data.cmd.stp) = 2, 1);
		}
	}
	printf("%s\n", cwd);
	return (0);
}
