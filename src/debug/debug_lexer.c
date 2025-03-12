/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:24:58 by keishii           #+#    #+#             */
/*   Updated: 2025/03/12 16:57:56 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_show_token_list(t_token_list *list)
{
	int	i;

	printf("\ntoken_list->num: %d\n", list->num);
	printf("\n");
	i = 0;
	while (i < list->num)
	{
		printf("token_list[%d]: %-10s token_type: %d\n",
			i, list->token_list[i].token,
			list->token_list[i].token_type);
		i++;
	}
}
