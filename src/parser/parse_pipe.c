/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:30:31 by keishii           #+#    #+#             */
/*   Updated: 2025/04/13 18:44:09 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	printf("parse_pipe called\n");
	if (helper->index < array->len
		&& array->tokens[helper->index].token_type == PIPE)
	{
		syntax_error("|");
		return (*exit_status = 2, 1);
	}
	if (parse_cmd(array, helper, envl, exit_status))
		return (1);
	printf("after parse_cmd, helper->node = %p\n", helper->node);
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
