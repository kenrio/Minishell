/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:31:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/24 17:36:41 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// this func() create pipe, and execute left cmd and right ast node.
// there is a "fd_in" to use input, but is not "fd_out". we don't need.
int	exec_ast_pipe(t_ast *ast_node, int fd_in, pid_t *pids)
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
	{
		perror("create pipe failed.");
		return (1);
	}
	exec_left_cmd(ast_node, fd_in, fd_pipe, pids);
	close(fd_pipe[1]);
	if (execute_ast(ast_node->u_data.pipe.right, fd_pipe[0], pids))
		return (1);
	close(fd_pipe[0]);
	return (0);
}

