/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:04:52 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/24 16:18:46 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void close_pipe(int fd_pipe[]);

// exec_ast_pipe() can only create pipe. this func don't use fork(). 
int	exec_ast_pipe(t_ast *ast_node, int fd_in, int fd_out, pid_t *pids)
{
    // pipeのとき、パイプを作り、execute_ast(left) &(right)を行う
    int    fd_pipe[2];

	// pipe生み出す。
    if (pipe(fd_pipe) == -1)
		return (1);

    // exec(left) & exec(right)
	if (execute_ast(ast_node->data.pipe.left, fd_in , fd_pipe[1], pids))
	{
		// left 実行がエラーだった場合の処理(//TODO fd_pipeいい感じに閉じないとかも)
		close_pipe(fd_pipe);
		return (1);
	}
	close (fd_pipe[1]);
	if (execute_ast(ast_node->data.pipe.right, fd_pipe[0], fd_out, pids))
	{
		// right 実行がエラーだった場合の処理(//TODO fd_pipeいい感じに閉じないとかも)
		close_pipe(fd_pipe);
		return (1);
	}
	close(fd_pipe[0]);
	return (0);
}


static void close_pipe(int fd_pipe[])
{
	if (fd_pipe[0] != -1)
		close(fd_pipe[0]);
	if (fd_pipe[1] != -1)	
		close(fd_pipe[1]);
}