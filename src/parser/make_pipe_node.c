/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:32:34 by keishii           #+#    #+#             */
/*   Updated: 2025/04/13 01:49:27 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ast	*allocate_ast_node(int *exit_status);
static int		allocate_lr_cmd_mem(t_ast **original,
					t_ast **left, t_ast **right, int *exit_status);

int	make_pipe_node(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	t_ast	*left_node;
	t_ast	*right_node;
	t_ast	*original_node;

	if (helper->node == NULL)
		return (1);
	original_node = helper->node;
	if (allocate_lr_cmd_mem(&helper->node, &left_node, &right_node, exit_status))
		return (1);
	helper->node = right_node;
	if (parse_pipe(array, helper, envl, exit_status))
	{
		free_ast(helper->node->u_data.pipe.left);
		free_ast(helper->node->u_data.pipe.right);
		helper->node = original_node;
		return (1);
	}
	helper->node = original_node;
	return (0);
}

static t_ast	*allocate_ast_node(int *exit_status)
{
	t_ast	*node;

	node = ft_calloc(1, sizeof(t_ast));
	if (!node)
		*exit_status = 1;
	return (node);
}

static int	allocate_lr_cmd_mem(t_ast **original,
			t_ast **left, t_ast **right, int *exit_status)
{
	*left = allocate_ast_node(exit_status);
	if (!(*left))
		return (1);
	*left = copy_ast(*original, exit_status);
	(*original)->type = NODE_PIPE;
	(*original)->u_data.pipe.left = *left;
	*right = allocate_ast_node(exit_status);
	if (!(*right))
	{
		free_ast(*left);
		return (1);
	}
	(*original)->u_data.pipe.right = *right;
	return (0);
}
