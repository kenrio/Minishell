/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:29:56 by keishii           #+#    #+#             */
/*   Updated: 2025/05/01 00:05:28 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numeric(const char *str);

int	execute_exit(t_ast *ast, t_envl *envl)
{
	long	exit_status;

	exit_status = *(ast->u_data.cmd.stp);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (ast->u_data.cmd.argv[1])
	{
		if (!is_numeric(ast->u_data.cmd.argv[1]))
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(ast->u_data.cmd.argv[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			free_ast(ast);
			destroy_envl(envl);
			exit(2);
		}
		if (ast->u_data.cmd.argv[2])
			return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO),
					*(ast->u_data.cmd.stp) = 1, 1);
		exit_status = ft_atoi(ast->u_data.cmd.argv[1]);
	}
	free_ast(ast);
	destroy_envl(envl);
	exit((unsigned char)exit_status);
}

static bool	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
