/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 14:16:40 by keishii           #+#    #+#             */
/*   Updated: 2025/03/31 15:12:17 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_cmd_node(t_ast *ast);
static void	free_redirects(t_redirect *redirect);

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	if (ast->type == NODE_CMD)
		free_cmd_node(ast);
	else if (ast->type == NODE_PIPE)
	{
		free_ast(ast->u_data.pipe.left);
		free_ast(ast->u_data.pipe.right);
	}
	free(ast);
}

static void	free_cmd_node(t_ast *ast)
{
	int	i;

	if (ast->u_data.cmd.name)
		free(ast->u_data.cmd.name);
	if (ast->u_data.cmd.path)
		free(ast->u_data.cmd.path);
	if (ast->u_data.cmd.argv)
	{
		i = 0;
		while (ast->u_data.cmd.argv[i])
		{
			free(ast->u_data.cmd.argv[i]);
			i++;
		}
		free(ast->u_data.cmd.argv);
	}
	if (ast->u_data.cmd.envp)
	{
		i = 0;
		while (ast->u_data.cmd.envp[i])
		{
			free(ast->u_data.cmd.envp[i]);
			i++;
		}
		free(ast->u_data.cmd.envp);
	}
	if (ast->u_data.cmd.redirects)
		free_redirects(ast->u_data.cmd.redirects);
}

static void	free_redirects(t_redirect *redirect)
{
	t_redirect	*current;
	t_redirect	*next;

	current = redirect;
	while (current)
	{
		next = current->next;
		if (current->file_name)
			free(current->file_name);
		free(current);
		current = next;
	}
}
