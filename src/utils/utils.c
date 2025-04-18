/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:22:39 by keishii           #+#    #+#             */
/*   Updated: 2025/04/17 14:33:54 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_message(void)
{
	printf("hello minishell\n");
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_doller(int c)
{
	return (c == '$');
}

int	is_env_char(int c)
{
	return (ft_isalnum(c) || (c == '_'));
}

void	exit_f(char *comment)
{
	perror(comment);
	exit(EXIT_FAILURE);
}
