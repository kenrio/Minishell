/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:54:25 by keishii           #+#    #+#             */
/*   Updated: 2025/04/30 21:44:01 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern sig_atomic_t	g_signal;

void	idle_handler(int signum)
{
	g_signal = signum;
	rl_done = 1;
}

void	exec_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
	}
}
