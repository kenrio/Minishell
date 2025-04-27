/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_component.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:47:50 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/27 19:50:26 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	setup_child_fd(int fd_in, int fd_out);
static void	check_fd(int fd_in, int fd_out);
static int	validate_cmd_path(t_ast *node);

void	exec_cmd(t_ast *node, int fd_in, int fd_out)
{
	set_exec_child_handler();
	check_fd(fd_in, fd_out);
	setup_child_fd(fd_in, fd_out);
	if (validate_cmd_path(node))
		exit(*node->u_data.cmd.stp);
	execve(node->u_data.cmd.path, node->u_data.cmd.argv,
		node->u_data.cmd.envp);
	exit_f("execve failed");
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

static	int	validate_cmd_path(t_ast *node)
{
	struct stat	st;
	char		*path;

	path = node->u_data.cmd.path;
	if (!path || access(path, F_OK) != 0)
	{
		ft_putstr_fd("Command not found.\n", STDERR_FILENO);
		return (*(node->u_data.cmd.stp) = 127, 1);
	}
	if (access(path, X_OK) != 0)
		return (perror(path), *(node->u_data.cmd.stp) = 126, 1);
	if (stat(path, &st) != 0)
		return (perror(path), *(node->u_data.cmd.stp) = 126, 1);
	if (!S_ISREG(st.st_mode) && !S_ISLNK(st.st_mode))
	{
		ft_putstr_fd("Permission denied.\n", STDERR_FILENO);
		return (*(node->u_data.cmd.stp) = 126, 1);
	}
	return (0);
}
