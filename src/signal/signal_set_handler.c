/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_set_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 20:56:39 by keishii           #+#    #+#             */
/*   Updated: 2025/04/06 21:19:53 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_idle_handler(void)
{
	struct sigaction	sig;

	// sig.sa_handler = idle_handler;
	// // sig.sa_flags = 0;
	sig.sa_handler = SIG_IGN;
}
