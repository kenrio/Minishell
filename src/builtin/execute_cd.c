/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:02:59 by keishii           #+#    #+#             */
/*   Updated: 2025/04/22 11:27:15 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_envl *lst, const char *key);

int	execute_cd(t_ast *ast, t_envl *envl)
{
	char	*pwd;
	char	*newpwd;
	char	*oldpwd;
	char	cwd[4096];

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (*(ast->u_data.cmd.stp) = 1, 1);
	if (!ast->u_data.cmd.argv[1] || chdir(ast->u_data.cmd.argv[1]) != 0)
		return (free(pwd), *(ast->u_data.cmd.stp) = 1, perror("cd"), 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (free(pwd), *(ast->u_data.cmd.stp) = 1, 1);
	oldpwd = pwd;
	pwd = ft_strjoin("OLDPWD=", oldpwd);
	free(oldpwd);
	newpwd = ft_strjoin("PWD=", cwd);
	if (!pwd || !newpwd
		|| envl_add_node(envl, pwd) != 0 || envl_add_node(envl, newpwd) != 0)
		return (free(pwd), free(newpwd), *(ast->u_data.cmd.stp) = 1, 1);
	return (free(pwd), free(newpwd), *(ast->u_data.cmd.stp) = 0, 0);
}

char	*get_env_value(t_envl *lst, const char *key)
{
	t_env_node	*curr;
	size_t		key_len;

	if (!lst || !key)
		return (NULL);
	curr = lst->head;
	key_len = ft_strlen(key);
	while (curr)
	{
		if (ft_strncmp(curr->value, key, key_len) == 0
			&& curr->value[key_len] == '=')
			return (curr->value + key_len + 1);
		curr = curr->next;
	}
	return (NULL);
}
