/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 01:41:22 by keishii           #+#    #+#             */
/*   Updated: 2025/04/22 18:00:27 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_list(t_envl *envl);
static bool	is_valid_key(const char *arg);

int	execute_export(t_ast *ast, t_envl *envl)
{
	int	i;

	if (!ast->u_data.cmd.argv[1])
	{
		print_export_list(envl);
		return (*(ast->u_data.cmd.stp) = 0, 0);
	}
	i = 1;
	while (ast->u_data.cmd.argv[i])
	{
		if (is_valid_key(ast->u_data.cmd.argv[i]))
		{
			if (ft_strchr(ast->u_data.cmd.argv[i], '='))
				if (envl_add_node(envl, ast->u_data.cmd.argv[i]) != 0)
					return (*(ast->u_data.cmd.stp) = 1, 1);
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

static void	print_export_list(t_envl *envl)
{
	t_env_node	*curr;

	curr = envl->head;
	while (curr)
	{
		printf("declare -x %s\n", curr->value);
		curr = curr->next;
	}
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
