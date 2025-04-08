/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:31:22 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/08 15:59:53 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern sig_atomic_t	g_signal;
static int			create_heredoc_pipe(const char *delimiter, char **envp, int *stp);

// <<
int	handle_heredoc(int *fd_in_, char *delimiter, char **envp, int *stp)
{
	int	temp;

	temp = create_heredoc_pipe(delimiter, envp, stp);
	if (temp == -1)
		return (1);
	if (*fd_in_ != STDIN_FILENO)
		close(*fd_in_);
	*fd_in_ = temp;
	return (0);
}



// this func() create pipe, and return pipe_output.
static	int	create_heredoc_pipe(const char *delimiter, char **envp, int *stp)
{
	int		fd_pipe[2];
	char	*line;
	// int		count;

	if (pipe(fd_pipe) == -1)
	{
		perror("pipe open failed.");
		return (-1);
	}
	// set_heredoc_child_handler();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			write(STDERR_FILENO, "minishell: warning: here-document delimited by eof\n\n", 51);
			break ;
		}
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		// count = ft_strlen(line);
		ft_putstr_fd(expand_doller_heredoc(line, envp, stp), fd_pipe[1]);
		write(fd_pipe[1], "\n", 1);
		free(line);
	}
	close(fd_pipe[1]);
	return (fd_pipe[0]);
}
