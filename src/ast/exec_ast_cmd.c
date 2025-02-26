/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:07:58 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/24 18:42:48 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	check_fd(int fd_in, int fd_out);
static	void	setup_child_fd(int fd_in, int fd_out);




// exec_ast_cmd() is used as follows.
// step1. if there is a redirect arrays, replace fd_in and fd_out.
// step2. fd_in & fd_out to std_in & std_out, use dup().
// step3. Execute fork(), and execute(). 
int	exec_ast_cmd(t_ast *ast_node, int fd_in, int fd_out, pid_t *pids)
{
    // このノードタイプ＝cmdの場合、コマンドを実行する。

	// 1: redirect配列に１つでもredirectが入っていた場合、リダイレクトにfd_in, fd_outを付け替える
	if (ast_node->data.cmd.redirects != NULL)
		handle_redirect();

	// null だったらそのまま抜ける


	// 2: redirect配列がない場合、単純にfd_inから読み取り、fd_outに書き込めばいい。
	execute_cmd();

	
	



	

	
}


// this func() replace fd_in & fd_out.
static	int	handle_redirect()
{
	
}


// 書き込む必要あるね.いったん入力先と出力先をわたしてみる
static	void	execute_cmd()
{
	
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