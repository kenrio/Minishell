/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 12:21:20 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/06 15:01:25 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	handle_r_out(int *fd_out, char *file_name);
static	int	handle_r_out_append(int *fd_out, char *file_name);
static	int	handle_r_in(int *fd_in, char *file_name);

// this func() can apply redirects_array to cmd input or output, in order.
// ex) curr = type:R_OUT, file_name:test1, next:node
int	handle_redirects(t_ast *node, int *fd_in_, int *fd_out_)
{
	int			ret;
	t_redirect	*curr;

	curr = node->u_data.cmd.redirects;
	if (!curr)
		return (1);
	ret = 0;
	while (curr)
	{
		if (curr->type == R_OUT)
			ret = handle_r_out(fd_out_, curr->file_name);
		else if (curr->type == R_OUT_APPEND)
			ret = handle_r_out_append(fd_out_, curr->file_name);
		else if (curr->type == R_IN)
			ret = handle_r_in(fd_in_, curr->file_name);
		else
			ret = handle_heredoc(fd_in_, curr->file_name, node->u_data.cmd.envp, node->u_data.cmd.stp);
		if (ret == 1)
			return (1);
		curr = curr->next;
	}
	return (0);
}

// >
static	int	handle_r_out(int *fd_out, char *file_name)
{
	int	temp;

	temp = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp < 0)
	{
		perror("file open failed.");
		return (1);
	}
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	*fd_out = temp;
	return (0);
}

// >>
static	int	handle_r_out_append(int *fd_out, char *file_name)
{
	int	temp;

	temp = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (temp < 0)
	{
		perror("file open failed.");
		return (1);
	}
	if (*fd_out != STDOUT_FILENO)
		close(*fd_out);
	*fd_out = temp;
	return (0);
}

// <
static	int	handle_r_in(int *fd_in, char *file_name)
{
	int	temp;

	temp = open(file_name, O_RDONLY);
	if (temp < 0)
	{
		perror("file open failed.");
		return (1);
	}
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = temp;
	return (0);
}
