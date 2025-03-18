/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:42:57 by keishii           #+#    #+#             */
/*   Updated: 2025/03/14 15:06:44 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_token_to_array(char *line, t_token_array *array,
		t_token_state *state, int *exit_status)
{
	int	len;

	len = state->current_index - state->start_index;
	if (len <= 0)
		return (0);
	array->tokens[state->token_index].token
		= (char *)ft_calloc(len + 1, sizeof(char));
	if (!array->tokens[state->token_index].token)
	{
		perror("ft_calloc");
		*exit_status = 1;
		return (1);
	}
	ft_strlcpy(array->tokens[state->token_index].token,
		&line[state->start_index], len + 1);
	array->tokens[state->token_index].token[len] = '\0';
	state->token_index++;
	return (0);
}
