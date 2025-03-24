/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:30:31 by keishii           #+#    #+#             */
/*   Updated: 2025/03/24 21:18:15 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_ast *node, t_token_array *array, t_parser_helper *p_help, char **envp, int *exit_status)
{
	t_ast	left_node;

	if (parse_cmd(&left_node, array, p_help, envp, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	if (p_help->index < array->len && array->tokens[p_help->index].token_type == PIPE)
	{
		p_help->index++;
		if (make_pipe_node(node, &left_node, array, p_help, envp, exit_status))
		{
			*exit_status = 1;
			return (1);
		}
		return (0);
	}
	*node = left_node;
	return (0);
}
