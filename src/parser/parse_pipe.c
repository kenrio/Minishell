/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:30:31 by keishii           #+#    #+#             */
/*   Updated: 2025/04/15 14:26:42 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	start_with_pipe(t_token_array *array, t_parse_helper *helper);

int	parse_pipe(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	if (start_with_pipe(array, helper))
		return (*exit_status = 2, 1);
	if (parse_cmd(array, helper, envl, exit_status))
		return (1);
	if (helper->node == NULL)
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
		return (make_pipe_node(array, helper, envl, exit_status));
	}
	return (0);
}

static int	start_with_pipe(t_token_array *array, t_parse_helper *helper)
{
	if (helper->index < array->len
		&& array->tokens[helper->index].token_type == PIPE)
	{
		syntax_error("|");
		return (1);
	}
	return (0);
}
