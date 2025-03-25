/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:31:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/24 17:36:41 by keishii          ###   ########.fr       */
=======
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:31:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/25 15:13:19 by tishihar         ###   ########.fr       */
>>>>>>> tsubasa/dev
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// this func() create pipe, and execute left cmd and right ast node.
// there is a "fd_in" to use input, but is not "fd_out". we don't need.
<<<<<<< HEAD
int	exec_ast_pipe(t_ast *ast_node, int fd_in, pid_t *pids)
=======
int	exec_ast_pipe(t_ast *ast_node, int fd_in, t_pids *pids)
>>>>>>> tsubasa/dev
{
	int	fd_pipe[2];

	if (pipe(fd_pipe) == -1)
	{
		perror("create pipe failed.");
		return (1);
	}
	exec_left_cmd(ast_node, fd_in, fd_pipe, pids);
	close(fd_pipe[1]);
<<<<<<< HEAD
	if (execute_ast(ast_node->u_data.pipe.right, fd_pipe[0], pids))
=======
	if (execute_ast(ast_node->data.pipe.right, fd_pipe[0], pids))
>>>>>>> tsubasa/dev
		return (1);
	close(fd_pipe[0]);
	return (0);
}

