/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:21:49 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/24 16:08:26 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// execute_ast() can use for running AST_NODE, and exec command or chain pipe.
// func call thisself multiple time. thus, this has recursion structure.
// こいつにトップノードを渡すと、すべて再帰で実行してくれます。
int    execute_ast(t_ast *ast_node, int fd_in, int fd_out, pid_t *pids)
{
    if (!ast_node)
        return (1);
    if (ast_node->type == NODE_PIPE)
	{
		if (exec_ast_pipe(ast_node, fd_in, fd_out, pids))
			return (1);
		return (0);
	}
    else if (ast_node->type == NODE_CMD)
	{
		if (exec_ast_cmd(ast_node, fd_in, fd_out, pids))
			return (1);
		return (0);
	}
    else
	{
        perror("unkonown node type.\n");
		return (1);
	}
}

