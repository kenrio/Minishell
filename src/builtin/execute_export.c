/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:41:22 by keishii           #+#    #+#             */
/*   Updated: 2025/04/20 23:32:57 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_key(const char *arg);

int	execute_export(t_ast *ast, t_envl *envl)
{
	t_env_node	*curr;
	char		*new_arg;
	int			i;

	if (!ast->u_data.cmd.argv[1])
	{
		curr = envl->head;
		while (curr)
		{
			printf("declare -x %s\n", curr->value);
			curr = curr->next;
		}
		return (0);
	}
	i = 1;
	while (ast->u_data.cmd.argv[i])
	{
		if (is_valid_key(ast->u_data.cmd.argv[i]))
		{
			if (ft_strchr(ast->u_data.cmd.argv[i], '='))
			{
				if (envl_add_node(envl, ast->u_data.cmd.argv[i]) != 0)
					return (*(ast->u_data.cmd.stp) = 1, 1);
			}
			else
			{
				new_arg = ft_strjoin(ast->u_data.cmd.argv[i], "=");
				if (!new_arg || envl_add_node(envl, new_arg) != 0)
				{
					free(new_arg);
					return (*(ast->u_data.cmd.stp) = 1, 1);
				}
				free(new_arg);
			}
		}
		else
		{
			ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
			return (*(ast->u_data.cmd.stp) = 1, 1);
		}
		i++;
	}
	return (*(ast->u_data.cmd.stp) = 0, 0);
}

static bool	is_valid_key(const char *arg)
{
	if (!arg || !(*arg))
		return (false);
	if (!ft_isalpha(*arg) && (*arg != '_'))
		return (false);
	while (*arg && *arg != '=')
	{
		if (!ft_isalnum(*arg) && *arg != '_')
			return (false);
		arg++;
	}
	return (true);
}
