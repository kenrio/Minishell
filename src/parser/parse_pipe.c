/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:30:31 by keishii           #+#    #+#             */
/*   Updated: 2025/03/21 23:31:00 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	t_ast	left_node;

	if (parse_cmd(&left_node, array, pos, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	if (*pos < array->len && array->tokens[*pos].token_type == PIPE)
	{
		(*pos)++;
		if (make_pipe_node(node, &left_node, array, pos, exit_status))
		{
			*exit_status = 1;
			return (1);
		}
		return (0);
	}
	*node = left_node;
	return (0);
}
