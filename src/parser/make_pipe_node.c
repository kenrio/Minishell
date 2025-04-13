/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:32:34 by keishii           #+#    #+#             */
/*   Updated: 2025/04/13 18:43:30 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static t_ast	*allocate_ast_node(int *exit_status);
// static int		allocate_lr_cmd_mem(t_ast *original,
// 					t_ast **left, t_ast **right, int *exit_status);

int	make_pipe_node(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	t_ast	*left_node;
	t_ast	*right_node;
	t_ast	*pipe_node;

	printf("make_pipe_node entered\n");
	printf("make_pipe_node: helper->node = %p\n", helper->node);
	if (helper->node == NULL)
	{
		printf("helper->node is NULL\n");
		return (1);
	}
	left_node = copy_ast(helper->node, exit_status);
	if (left_node && left_node->type == NODE_CMD)
		printf("copy_ast: cmd = %s\n", left_node->u_data.cmd.name);
	if (parse_pipe(array, helper, envl, exit_status))
	{
		free_ast(left_node);
		return (1);
	}
	right_node = helper->node;
	if (!right_node)
	{
		free_ast(left_node);
		return (1);
	}
	pipe_node = ft_calloc(1, sizeof(t_ast));
	if (!pipe_node)
	{
		free_ast(left_node);
		free_ast(right_node);
		return (*exit_status = 1, 1);
	}
	pipe_node->type = NODE_PIPE;
	pipe_node->u_data.pipe.left = left_node;
	pipe_node->u_data.pipe.right = right_node;
	helper->node = pipe_node;
	return (0);
}

// static t_ast	*allocate_ast_node(int *exit_status)
// {
// 	t_ast	*node;

// 	node = ft_calloc(1, sizeof(t_ast));
// 	if (!node)
// 		*exit_status = 1;
// 	return (node);
// }

// static int	allocate_lr_cmd_mem(t_ast *original,
// 			t_ast **left, t_ast **right, int *exit_status)
// {
// 	// *left = allocate_ast_node(exit_status);
// 	*left = copy_ast(original, exit_status);
// 	if (!(*left))
// 		return (1);
// 	*right = ft_calloc(1, sizeof(t_ast));
// 	if (!(*right))
// 	{
// 		free_ast(*left);
// 		return (1);
// 	}
// 	original->type = NODE_PIPE;
// 	original->u_data.pipe.left = *left;
// 	original->u_data.pipe.right = *right;
// 	return (0);
// }
