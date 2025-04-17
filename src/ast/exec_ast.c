/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:21:49 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/17 17:37:51 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	bool	is_builtin(t_ast *ast_node);
static	int		execute_builtin(t_ast *ast_node, t_envl *envl, int *status);

// this func() can run ast_node.
// you should pass ast_top_node and ast_status_poipnter.
int	run_ast(t_ast *ast_node, t_envl *envl, int *status)
{
	t_pids	pids;

	if (!ast_node)
		return (1);
	init_pids(&pids);
	if (is_builtin(ast_node))
	{
		if (execute_builtin(ast_node, envl, status))
			return (1);
	}
	else
	{
		if (execute_ast(ast_node, STDIN_FILENO, &pids))
		{
			wait_pids(&pids, status);
			destroy_pids(&pids);
			return (1);
		}
		wait_pids(&pids, status);
		destroy_pids(&pids);
	}
	return (0);
}

// execute_ast() can use for running AST_NODE, and exec command or chain pipe.
// func() call thisself multiple time. thus, this has recursion structure.
// if you execute this func() as top_node, you set "fd_in" to "STDIN_FILENO".
int	execute_ast(t_ast *ast_node, int fd_in, t_pids *pids)
{
    if (!ast_node)
        return (1);
    if (ast_node->type == NODE_PIPE)
	{
		if (exec_ast_pipe(ast_node, fd_in, pids))
			return (1);
		return (0);
	}
    else if (ast_node->type == NODE_CMD)
	{
		exec_right_cmd(ast_node, fd_in, pids);
		return (0);
	}
    else
	{
        perror("unkonown node type.\n");
		return (1);
	}
}

static	bool	is_builtin(t_ast *ast_node)
{
	char	*cmd_name;

	cmd_name = ast_node->u_data.cmd.name;
	return (
		ast_node->type == NODE_CMD 
		&& (ft_strcmp(cmd_name, "echo") == 0
			|| ft_strcmp(cmd_name, "cd") == 0
			|| ft_strcmp(cmd_name, "pwd") == 0
			|| ft_strcmp(cmd_name, "export") == 0
			|| ft_strcmp(cmd_name, "unset") == 0
			|| ft_strcmp(cmd_name, "env") == 0
			|| ft_strcmp(cmd_name, "exit") == 0
		)
	);
}

static	int	execute_builtin(t_ast *ast_node, t_envl *envl, int *status)
{
	char	*cmd_name;
	(void) status;
	
	cmd_name = ast_node->u_data.cmd.name;

	//TODO
	// もしもechoコマンドだった場合、execute_echo()が実行される。
	// 各コマンド実行関数は、成功なら０、失敗なら１を返してほしい
	// ex) int	execute_echo(ast_node, status), int	execute_echo(ast_node)toka
	// buitin関数はbuitin/にあつめてもってこよう
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (execute_echo(ast_node));
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (execute_cd(ast_node, envl));
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (execute_pwd());
	else if (ft_strcmp(cmd_name, "export") == 0)
		return (execute_export(ast_node, envl));
	else if (ft_strcmp(cmd_name, "unset") == 0)
		return (execute_unset(ast_node, envl));
	else if (ft_strcmp(cmd_name, "env") == 0)
		return (execute_env(ast_node));
	else if (ft_strcmp(cmd_name, "exit") == 0)
		return (execute_exit(ast_node, envl));
	else
		return (1);
}
