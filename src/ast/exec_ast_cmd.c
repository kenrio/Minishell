/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:07:58 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/24 16:16:23 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	check_fd(int fd_in, int fd_out);
static	void	setup_child_fd(int fd_in, int fd_out);




// ast_cmd_helper
int	exec_ast_cmd(t_ast *ast_node, int fd_in, int fd_out, pid_t *pids)
{
    // このノードタイプ＝cmdの場合、コマンドを実行する。
	// 基本はfd_inから読み取り、fd_outに書き込む。リダイレクト処理

	

	
}


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

static	void	setup_child_fd(int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	if (fd_out != -1)
	{
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}