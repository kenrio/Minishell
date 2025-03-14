/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 14:22:39 by keishii           #+#    #+#             */
/*   Updated: 2025/03/14 19:14:04 by tishihar         ###   ########.fr       */
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

int	is_doller(int	c)
{
	return (c == '$');
}
