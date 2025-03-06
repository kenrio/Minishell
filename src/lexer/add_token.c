/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:42:57 by keishii           #+#    #+#             */
/*   Updated: 2025/03/06 19:14:17 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token(char *line, t_token_list *list,
		t_token_state *state, int *exit_status)
{
	int	len;

	len = state->current_index - state->start_index;
	if (len <= 0)
		return (0);
	list->token_list[state->token_index].token
		= NULL;
	// list->token_list[state->token_index].token
	// 	= (char *)malloc(sizeof(char) * (len + 1));
	if (!list->token_list[state->token_index].token)
	{
		printf("error: malloc\n");
		*exit_status = 1;
		return (1);
	}
	ft_strlcpy(list->token_list[state->token_index].token,
			&line[state->start_index], len + 1);
	list->token_list[state->token_index].token[len] = '\0';
	state->token_index++;
	return (0);
}
