/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:21:49 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/27 17:22:07 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this func() can run ast_node.
// you should pass ast_top_node.
int	run_ast(t_ast *ast_node)
{
	// この関数でpidsを用意してexecute_astを行う
	

	// ast_top_nodeがcmdtypeの場合(build_in関数)はここに記述

	// normal_execute()
	if (execute_ast(ast_node, STDIN_FILENO, pids))
	{
		// パイプとかがうまく行かなくてエラー戻りしてきた場合の処理
	}


	// wait処理


	return (0);
}

// execute_ast() can use for running AST_NODE, and exec command or chain pipe.
// func() call thisself multiple time. thus, this has recursion structure.
// if you execute this func() as top_node, you set "fd_in" to "STDIN_FILENO".
int	execute_ast(t_ast *ast_node, int fd_in, pid_t *pids)
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

