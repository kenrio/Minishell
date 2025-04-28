/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 19:59:48 by keishii           #+#    #+#             */
/*   Updated: 2025/04/28 16:59:24 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_pwd(t_ast *ast)
{
	char	*arg;
	char	*pwd;

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
	pwd = get_env_value_bykey(ast->u_data.cmd.envp, "PWD");
	if (!pwd)
		printf("can't find pwd.\n");
	else
		printf("%s\n", pwd);
	return (*(ast->u_data.cmd.stp) = 0, 0);
}