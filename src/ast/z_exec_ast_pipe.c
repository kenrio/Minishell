/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_exec_ast_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:32:03 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/27 17:50:05 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static	void 	close_pipe(int fd_pipe[]);
// static	void	wait_left_right();
// static	void	exec_left(t_ast *ast_node, int fd_in, int fd_pipe[], pid_t *pids);
// static	void	exec_right(t_ast *ast_node, int fd_pipe[], int fd_out, pid_t *pids);


// exec_ast_pipe() handle a pipe.
// use fork(), separate left and right processes, and execute_ast() in each;
// int	exec_ast_pipe(t_ast *ast_node, int fd_in, int fd_out, pid_t *pids)
// {
// 	int		fd_pipe[2];

// 	// pipe生み出す。
//     if (pipe(fd_pipe) == -1)
// 	{
// 		perror("crate pipe failed.");
// 		return (1);
// 	}
	
// 	// pipeがある状態でleftとrightをfork()する。
// 	exec_left(ast_node->data.pipe.left, fd_in, fd_pipe, pids);
// 	exec_right(ast_node->data.pipe.right, fd_pipe, fd_out, pids);

// 	// 用済みなので速攻でpipeを閉じる
// 	close_pipe(fd_pipe);
	
// 	// wait処理
// 	wait_left_right();

// 	// return 
// 	return (0);
// }

// // this function can close pipe, riterally.
// static	void	close_pipe(int fd_pipe[])
// {
// 	if (fd_pipe[0] != -1)
// 		close(fd_pipe[0]);
// 	if (fd_pipe[1] != -1)	
// 		close(fd_pipe[1]);
// }

// // this function wait a pipe_fork().
// static	void	wait_left_right()
// {
// 	int count;

// 	count = 2;
// 	while (count--)
// 		wait(NULL);
// }

// // riterally.
// static	void	exec_left(t_ast *ast_node, int fd_in, int fd_pipe[], pid_t *pids)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("pipe fork failed.");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		// 要らない方を消す
// 		close(fd_pipe[0]);

// 		// execute_ast();
// 		if (execute_ast(ast_node, fd_in, fd_pipe[1], pids))
// 		{
// 			// 実行がエラーだった場合の処理
// 			exit(EXIT_FAILURE);
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// }

// // riterally.
// static	void	exec_right(t_ast *ast_node, int fd_pipe[], int fd_out, pid_t *pids)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		perror("pipe fork failed.");
// 		exit(EXIT_FAILURE);
// 	}
// 	else if (pid == 0)
// 	{
// 		// 要らない方を消す
// 		close(fd_pipe[1]);

// 		// execute_ast();
// 		if (execute_ast(ast_node, fd_pipe[0], fd_out, pids))
// 		{
// 			// 実行がエラーだった場合の処理
// 			exit(EXIT_FAILURE);
// 		}
// 		exit(EXIT_SUCCESS);
// 	}
// }

