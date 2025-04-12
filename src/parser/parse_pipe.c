/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:30:31 by keishii           #+#    #+#             */
/*   Updated: 2025/04/12 01:34:53 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	if (helper->index < array->len
		&& array->tokens[helper->index].token_type == PIPE)
	{
		syntax_error("|");
		return (*exit_status = 2, 1);
	}
	if (parse_cmd(array, helper, envl, exit_status))
		return (1);
	if (helper->index < array->len
		&& array->tokens[helper->index].token_type == PIPE)
	{
		helper->index++;
		if (helper->index >= array->len 
			|| array->tokens[helper->index].token_type == PIPE)
		{
			syntax_error("|");
			free_ast(helper->node);
			helper->node = NULL;
			return (*exit_status = 2, 1);
		}
		if (make_pipe_node(array, helper, envl, exit_status))
			return (*exit_status = 1, 1);
		return (0);
	}
	return (0);
}
