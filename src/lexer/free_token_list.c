/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:03:28 by keishii           #+#    #+#             */
/*   Updated: 2025/03/14 15:09:02 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_array(t_token_array *array)
{
	int	i;

	i = 0;
	if (!array || !array->tokens)
		return ;
	while (i < array->len)
	{
		if (array->tokens[i].token)
			free(array->tokens[i].token);
		i++;
	}
	free(array->tokens);
	array->tokens = NULL;
}
