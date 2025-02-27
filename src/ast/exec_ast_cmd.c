/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:07:58 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/27 18:03:53 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static	void	setup_child_fd(int fd_in, int fd_out);
static	void	check_fd(int fd_in, int fd_out);






// exec_ast_cmd() is used as follows.
// step1. if there is a redirect arrays, replace fd_in and fd_out.
// step2. fd_in & fd_out to std_in & std_out, use dup().
// step3. Execute fork(), and execute(). 
void	exec_right_cmd(t_ast *node, int fd_in, pid_t *pids)
{
	pid_t	pid;

	// fork()して子プロセスで処理をする
	// fd_inとリダイレクト先(fd_out)を付け替えてから実行
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed.");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		check_fd(fd_in, STDOUT_FILENO);
		setup_child_fd(fd_in, STDOUT_FILENO);
		execve(node->data.cmd.path, node->data.cmd.argv, node->data.cmd.envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		// pid追加
		pids_push_back(pids, pid);
	}
	
}


// this func() execute cmd, and update pids.
void	exec_left_cmd(t_ast *node, int fd_in, int fd_pipe[], pid_t *pids)
{
	pid_t	pid;

	// fork()して子プロセスで処理をする
	// fd_inとfd_pipe[1]に入出力先を入れ替えてから実行している。
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed.");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		check_fd(fd_in, fd_pipe[1]);
		setup_child_fd(fd_in, fd_pipe[1]);
		execve(node->data.cmd.path, node->data.cmd.argv, node->data.cmd.envp);
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		// pid追加
		pids_push_back(pids, pid);
	}
}


// this func() determines if the input is correct.
static	void	check_fd(int fd_in, int fd_out)
{
	if (fd_in == -1)
	{
		perror("fd_in is not open");
		exit(EXIT_FAILURE);
	}
	if (fd_out == -1)
	{
		perror("fd_out is not open");
		exit(EXIT_FAILURE);
	}
}

// this func() is set "fd_in" to STDIN, and "fd_out" to STD_OUT
// if in or out isn't right shape, this is not the case.
static	void	setup_child_fd(int fd_in, int fd_out)
{
	// ここでfd_inが-1になるケースはリダイレクトが-1, もしくは初期inが-1か。
	if (fd_in != -1 || fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1 || fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}



//TODO:redirect対応とpids登録





