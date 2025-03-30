/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:32:34 by keishii           #+#    #+#             */
/*   Updated: 2025/03/30 20:51:42 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pipe_node(t_token_array *array, t_parse_helper *helper, char **envp, int *exit_status)
{
	t_ast	*left_node;
	t_ast	*original_node;

	left_node = ft_calloc(1, sizeof(t_ast));
	if (!left_node)
		return (*exit_status = 1, 1);
	*left_node = *(helper->node);
	helper->node->type = NODE_PIPE;
	helper->node->u_data.pipe.left = left_node;
	helper->node->u_data.pipe.right = ft_calloc(1, sizeof(t_ast));
	if (!helper->node->u_data.pipe.right)
	{
		free(helper->node->u_data.pipe.left);
		return (*exit_status = 1, 1);
	}
	original_node = helper->node;
	helper->node = helper->node->u_data.pipe.right;
	if (parse_pipe(array, helper, envp, exit_status))
	{
		free(helper->node->u_data.pipe.left);
		free(helper->node->u_data.pipe.right);
		return (*exit_status = 1, 1);
	}
	helper->node = original_node;
	return (0);
}
