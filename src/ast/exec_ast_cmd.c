/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:07:58 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/27 19:52:28 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exec_ast_cmd() is used as follows.
// step1. if there is a redirect arrays, replace fd_in and fd_out.
// step2. fd_in & fd_out to std_in & std_out, use dup().
// step3. Execute fork(), and execute(). 
void	exec_right_cmd(t_ast *node, int fd_in, t_pids *pids)
{
	pid_t	pid;
	int		fd_out;
	int		fd_in_tmp;

	fd_out = STDOUT_FILENO;
	fd_in_tmp = fd_in;
	if (node->u_data.cmd.redirects)
		if (handle_redirects(node, &fd_in, &fd_out))
			return ;
	set_exec_handler();
	pid = fork();
	if (pid < 0)
		exit_f("fork failed.");
	else if (pid == 0)
	{
		exec_cmd(node, fd_in, fd_out);
	}
	else
	{
		if (fd_in_tmp != STDIN_FILENO)
			close(fd_in_tmp);
		pids_push_back(pids, pid);
	}
}

// this func() execute cmd, and update pids.
// input by fd_in, output to fd_pipe[1];
void	exec_left_cmd(t_ast *node, int fd_in, int fd_pipe[], t_pids *pids)
{
	pid_t	pid;
	int		fd_out;
	int		fd_in_tmp;

	fd_out = fd_pipe[1];
	fd_in_tmp = fd_in;
	if (node->u_data.cmd.redirects)
		if (handle_redirects(node, &fd_in, &fd_out))
			return ;
	set_exec_handler();
	pid = fork();
	if (pid < 0)
		exit_f("fork failed.");
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		exec_cmd(node, fd_in, fd_out);
	}
	else
	{
		if (fd_in_tmp != STDIN_FILENO)
			close(fd_in_tmp);
		close(fd_pipe[1]);
		pids_push_back(pids, pid);
	}
}
