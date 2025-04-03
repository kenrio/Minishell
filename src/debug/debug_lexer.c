/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:24:58 by keishii           #+#    #+#             */
/*   Updated: 2025/03/22 14:38:11 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_tokens(t_token_array *array)
{
	int	i;

	printf("\ntoken_array->len: %d\n", array->len);
	printf("\n");
	i = 0;
	while (i < array->len)
	{
		printf("tokens[%d]: %-10s token_type: %d\n",
			i, array->tokens[i].token,
			array->tokens[i].token_type);
		i++;
	}
}
