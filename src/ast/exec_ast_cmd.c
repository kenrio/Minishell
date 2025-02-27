/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:07:58 by tishihar          #+#    #+#             */
/*   Updated: 2025/02/27 13:11:36 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// exec_ast_cmd() is used as follows.
// step1. if there is a redirect arrays, replace fd_in and fd_out.
// step2. fd_in & fd_out to std_in & std_out, use dup().
// step3. Execute fork(), and execute(). 
int	exec_right_cmd(t_ast *ast_node, int fd_in, pid_t *pids)
{
    // このノードタイプ＝cmdの場合、コマンドを実行する。

	// 1: redirect配列に１つでもredirectが入っていた場合、リダイレクトにfd_in, fd_outを付け替える
	if (ast_node->data.cmd.redirects != NULL)
		handle_redirect();

	// 2: 単純にfd_inから読み取り、fd_outに書き込めばいい。

	
}


// this func() execute cmd, and update pids.
int	exec_left_cmd(t_ast *node, int fd_in, int fd_pipe[], pid_t *pids)
{
	pid_t	pid;

	// redirect情報がある場合、STD_INとSTD_OUTを書き換える。
	if (node->data.cmd.redirects != NULL)
		handle_redirect();


	// fork()して子プロセスで処理をする
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed.");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// 要らない方を閉じる
		close(fd_pipe[0]);


		// fdの付け替え

		




		
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