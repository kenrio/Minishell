/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:31:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/27 13:18:51 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// this function create pipe, and execute left cmd and right node .
int	exec_ast_pipe(t_ast *ast_node, int fd_in, pid_t *pids)
{
	int	fd_pipe[2];

	// pipeをつくる
	if (pipe(fd_pipe) == -1)
	{
		perror("create pipe failed.");
		return (1);
	}

	// 左コマンドの実行
	if (exec_left_cmd(ast_node, fd_in, fd_pipe, pids))
		return (1);

	// close[0]
	close(fd_pipe[1]);// 書き込み口を消す

	// 右ノードの実行;
	if (execute_ast(ast_node->data.pipe.right, fd_pipe[0], pids))// 読み取り口が必要
		return (1);

	return (0);
}

