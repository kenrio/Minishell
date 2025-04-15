/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:32:34 by keishii           #+#    #+#             */
/*   Updated: 2025/04/15 14:26:53 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*set_pipe_data(t_ast *left, t_ast *right);

int	make_pipe_node(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	t_ast	*left_node;
	t_ast	*pipe_node;

	if (!helper->node)
		return (1);
	left_node = copy_ast(helper->node, exit_status);
	if (!left_node)
		return (*exit_status = 1, 1);
	if (parse_pipe(array, helper, envl, exit_status))
		return (free_ast(left_node), 1);
	if (!helper->node)
		return (free_ast(left_node), *exit_status = 1, 1);
	pipe_node = set_pipe_data(left_node, helper->node);
	if (!pipe_node)
	{
		free_ast(left_node);
		free_ast(helper->node);
		helper->node = NULL;
		return (*exit_status = 1, 1);
	}
	helper->node = pipe_node;
	return (0);
}

static t_ast	*set_pipe_data(t_ast *left, t_ast *right)
{
	t_ast	*pipe_node;

	pipe_node = ft_calloc(1, sizeof(t_ast));
	if (!pipe_node)
		return (NULL);
	pipe_node->type = NODE_PIPE;
	pipe_node->u_data.pipe.left = left;
	pipe_node->u_data.pipe.right = right;
	return (pipe_node);
}
