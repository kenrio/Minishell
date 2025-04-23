/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:07:58 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/23 16:24:10 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_fd(int fd_in, int fd_out);
static void	check_fd(int fd_in, int fd_out);
static int	is_valid_cmd(char *path, char *name);

// exec_ast_cmd() is used as follows.
// step1. if there is a redirect arrays, replace fd_in and fd_out.
// step2. fd_in & fd_out to std_in & std_out, use dup().
// step3. Execute fork(), and execute(). 
void	exec_right_cmd(t_ast *node, int fd_in, t_pids *pids)
{
	pid_t	pid;
	int		fd_out;

	fd_out = STDOUT_FILENO;
	if (node->u_data.cmd.redirects)
		if (handle_redirects(node, &fd_in, &fd_out))
			return ;
	set_exec_handler();
	pid = fork();
	if (pid < 0)
		exit_f("fork failed.");
	else if (pid == 0)
	{
		set_exec_child_handler();
		check_fd(fd_in, fd_out);
		setup_child_fd(fd_in, fd_out);
		*(node->u_data.cmd.stp) = is_valid_cmd(node->u_data.cmd.path, node->u_data.cmd.name);
		if (*node->u_data.cmd.stp)
			exit(*node->u_data.cmd.stp);
		execve(node->u_data.cmd.path, node->u_data.cmd.argv,
			node->u_data.cmd.envp);
		exit_f("execve failed");
	}
	else
		pids_push_back(pids, pid);
}

// this func() execute cmd, and update pids.
// input by fd_in, output to fd_pipe[1];
void	exec_left_cmd(t_ast *node, int fd_in, int fd_pipe[], t_pids *pids)
{
	pid_t	pid;
	int		fd_out;

	fd_out = fd_pipe[1];
	if (node->u_data.cmd.redirects)
		if (handle_redirects(node, &fd_in, &fd_out))
			return ;
	set_exec_handler();
	pid = fork();
	if (pid < 0)
		exit_f("fork failed.");
	else if (pid == 0)
	{
		set_exec_child_handler();
		close(fd_pipe[0]);
		check_fd(fd_in, fd_out);
		setup_child_fd(fd_in, fd_out);
		*(node->u_data.cmd.stp) = is_valid_cmd(node->u_data.cmd.path, node->u_data.cmd.name);
		if (*node->u_data.cmd.stp)
			exit(*node->u_data.cmd.stp);
		execve(node->u_data.cmd.path, node->u_data.cmd.argv,
			node->u_data.cmd.envp);
		exit_f("execve failed");
	}
	else
		pids_push_back(pids, pid);
}

// this func() determines if the input is correct.
static void	check_fd(int fd_in, int fd_out)
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
// The case where fd_in is -1 here is the case where the redirection is -1.
// THE TRUE CASE: fd_out is appropriate, and, fd_out is not STDOUT
static void	setup_child_fd(int fd_in, int fd_out)
{
	if (fd_in != -1 && fd_in != STDIN_FILENO)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1 && fd_out != STDOUT_FILENO)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}

static	int	is_valid_cmd(char *cmd_path, char *cmd_name)
{
	struct stat	st;

	// if (!cmd_path)
	// {
	// 	if (cmd_name)
	// 	{
	// 		ft_putstr_fd("Command not found.\n", STDERR_FILENO);
	// 		return (1);
	// 	}
	// 	else
	// 		return (1);
	// }
	(void)cmd_name;
	if (!cmd_path || access(cmd_path, F_OK) != 0)
	{
		ft_putstr_fd("Command not found.\n", STDERR_FILENO);
		return (127);
	}
	if (access(cmd_path, X_OK) != 0)
	{
		perror(cmd_path);
		return (126);
	}
	if (stat(cmd_path, &st) != 0)
	{
		perror(cmd_path);
		return (126);
	}
	if (!S_ISREG(st.st_mode) && !S_ISLNK(st.st_mode))
	{
		ft_putstr_fd("Persmission denied.\n", STDERR_FILENO);
		return (126);
	}
	return (0);
}
