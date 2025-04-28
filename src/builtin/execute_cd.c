/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:02:59 by keishii           #+#    #+#             */
/*   Updated: 2025/04/28 16:58:14 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cd(t_ast *ast, t_envl **envl)
{
	char	*old_pwd;
	char	new_pwd[4096];
	char	*old_node;
	char	*new_node;
	t_envl	*cpy_envl;

	old_pwd = get_env_value_bykey(ast->u_data.cmd.envp, "PWD");
	if (!old_pwd)
		return (*(ast->u_data.cmd.stp) = 1, perror("can not find ENVKEY: PWD\n"), 1);
	if (!ast->u_data.cmd.argv[1] || chdir(ast->u_data.cmd.argv[1]) != 0)
		return (*(ast->u_data.cmd.stp) = 1, perror("cd is only supports relative and absolute path."), 1);
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (*(ast->u_data.cmd.stp) = 1, 1);
	old_node = ft_strjoin("OLDPWD=", old_pwd);
	new_node = ft_strjoin("PWD=", new_pwd);
	cpy_envl = envl_clone(*envl);
	if (!old_node || !new_node || !cpy_envl || envl_add_node(cpy_envl, old_node) != 0 || envl_add_node(cpy_envl, new_node) != 0)
		return (free(old_node), free(new_node), destroy_envl(cpy_envl) , perror("cd failed."),*(ast->u_data.cmd.stp) = 1, 1);
	destroy_envl(*envl);
	*envl = cpy_envl;
	return (free(old_node), free(new_node),*(ast->u_data.cmd.stp) = 0, 0);
}
