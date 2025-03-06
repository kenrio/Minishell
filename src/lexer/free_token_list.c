/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:03:28 by keishii           #+#    #+#             */
/*   Updated: 2025/03/06 19:09:01 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token_list *list)
{
	int	i;

	i = 0;
	if (!list || !list->token_list)
		return ;
	while (i < list->num)
	{
		if (list->token_list[i].token)
			free(list->token_list[i].token);
		i++;
	}
	free(list->token_list);
	list->token_list = NULL;
}
