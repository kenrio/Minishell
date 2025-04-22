/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:34:37 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/22 11:30:57 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dispatch_builtin(t_ast *ast_node, t_envl *envl, int *status);
static int	prepare_fd(int *save_stdin, int *save_stdout,
				int fd_in, int fd_out);
static void	put_away_fd(int save_stdin, int save_stdout, int fd_in, int fd_out);

int	execute_builtin(t_ast *ast_node, t_envl *envl, int *status)
{
	int		fd_in;
	int		fd_out;
	int		save_stdin;
	int		save_stdout;
	int		ret;

	fd_in = STDIN_FILENO;
	fd_out = STDOUT_FILENO;
	if (ast_node->u_data.cmd.redirects)
		if (handle_redirects(ast_node, &fd_in, &fd_out))
			return (1);
	if (prepare_fd(&save_stdin, &save_stdout, fd_in, fd_out))
		return (1);
	ret = dispatch_builtin(ast_node, envl, status);
	put_away_fd(save_stdin, save_stdout, fd_in, fd_out);
	return (ret);
}

bool	is_builtin(t_ast *ast_node)
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

static int	dispatch_builtin(t_ast *ast_node, t_envl *envl, int *status)
{
	char	*cmd_name;

	(void) status;
	cmd_name = ast_node->u_data.cmd.name;
	if (ft_strcmp(cmd_name, "echo") == 0)
		return (execute_echo(ast_node));
	else if (ft_strcmp(cmd_name, "cd") == 0)
		return (execute_cd(ast_node, envl));
	else if (ft_strcmp(cmd_name, "pwd") == 0)
		return (execute_pwd(ast_node));
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

static int	prepare_fd(int *save_stdin, int *save_stdout, int fd_in, int fd_out)
{
	*save_stdin = dup(STDIN_FILENO);
	*save_stdout = dup(STDOUT_FILENO);
	if (*save_stdin == -1 || *save_stdout == -1)
	{
		perror("prepare dup failed.");
		return (1);
	}
	if (fd_in != STDIN_FILENO && dup2(fd_in, STDIN_FILENO) == -1)
		return (perror("prepare dup2 failed."), 1);
	if (fd_out != STDOUT_FILENO && dup2(fd_out, STDOUT_FILENO) == -1)
		return (perror("prepare dup2 failed."), 1);
	return (0);
}

static void	put_away_fd(int save_stdin, int save_stdout, int fd_in, int fd_out)
{
	if (dup2(save_stdin, STDIN_FILENO) == -1
		|| dup2(save_stdout, STDOUT_FILENO) == -1)
		perror("put away dup2 failed.");
	close(save_stdin);
	close(save_stdout);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
}
