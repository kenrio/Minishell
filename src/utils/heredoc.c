/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:31:22 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/05 17:28:57 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	create_heredoc_pipe(const char *delimiter);

// <<
int	handle_heredoc(int *fd_in_, char *delimiter)
{
	int	temp;

	temp = create_heredoc_pipe(delimiter);
	if (temp == -1)
		return (1);
	if (*fd_in_ != STDIN_FILENO)
		close(*fd_in_);
	*fd_in_ = temp;
	return (0);
}



// this func() create pipe, and return pipe_output.
static	int	create_heredoc_pipe(const char *delimiter)
{
	int		fd_pipe[2];
	char	*line;
	int		count;

	if (pipe(fd_pipe) == -1)
	{
		perror("pipe open failed.");
		return (-1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		count = ft_strlen(line);
		write(fd_pipe[1], line, count);
		write(fd_pipe[1], "\n", 1);
		free(line);
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
