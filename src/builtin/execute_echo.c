/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 16:29:27 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/20 23:28:51 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_all_n(const char *arg);

int	execute_echo(t_ast *ast)
{
	int		i;
	bool	newline;

	i = 1;
	newline = true;
	while (ast->u_data.cmd.argv[i]
		&& ft_strncmp(ast->u_data.cmd.argv[i], "-n", 2) == 0
		&& is_all_n(ast->u_data.cmd.argv[i] + 2))
	{
		newline = false;
		i++;
	}
	while (ast->u_data.cmd.argv[i])
	{
		ft_putstr_fd(ast->u_data.cmd.argv[i], STDOUT_FILENO);
		if (ast->u_data.cmd.argv[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return(*(ast->u_data.cmd.stp) = 0, 0);
}

static bool is_all_n(const char *arg)
{
	while (*arg)
	{
		if (*arg != 'n')
			return (false);
		arg++;
	}
	return (true);
}
