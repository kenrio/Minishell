/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 17:31:22 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/11 12:29:39 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_signal;
static int			create_heredoc_pipe(const char *delimiter,
						char **envp, int *stp);
static void			heredoc_loop(const char *delimiter, int fd_pipe[2],
						char **envp, int *stp);
static void			heredoc_eof_warning(const char *delimiter);

// <<
int	handle_heredoc(int *fd_in_, char *delimiter, char **envp, int *stp)
{
	int	temp;

	temp = create_heredoc_pipe(delimiter, envp, stp);
	if (WIFSIGNALED(*stp) && WTERMSIG(*stp) == SIGINT)
	{
		*fd_in_ = temp;
		return (2);
	}
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
	pid_t	pid;

	if (pipe(fd_pipe) == -1)
		return (perror("pipe open failed."), -1);
	set_heredoc_handler();
	pid = fork();
	if (pid == -1)
		return (perror("fork"), close(fd_pipe[0]), close(fd_pipe[1]), -1);
	if (pid == 0)
	{
		set_heredoc_child_handler();
		close(fd_pipe[0]);
		heredoc_loop(delimiter, fd_pipe, envp, stp);
		close(fd_pipe[1]);
		exit(0);
	}
	else
	{
		close(fd_pipe[1]);
		waitpid(pid, stp, 0);
		if (WIFSIGNALED(*stp) && WTERMSIG(*stp) == SIGINT)
			return (write(STDOUT_FILENO, "\n", 1), fd_pipe[0]);
	}
	return (fd_pipe[0]);
}

static void	heredoc_loop(const char *delimiter, int fd_pipe[2],
				char **envp, int *stp)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (heredoc_eof_warning(delimiter));
		if (ft_strcmp(line, delimiter) == 0)
			return (free(line));
		expanded = expand_doller_heredoc(line, envp, stp);
		if (!expanded)
			return (free(line));
		ft_putstr_fd(expanded, fd_pipe[1]);
		write(fd_pipe[1], "\n", 1);
		free(line);
		free(expanded);
	}
}

static void	heredoc_eof_warning(const char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document \
delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd((char *)delimiter, STDERR_FILENO);
	ft_putstr_fd("')", STDERR_FILENO);
}
