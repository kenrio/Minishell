/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:32:34 by keishii           #+#    #+#             */
/*   Updated: 2025/03/29 13:04:14 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pipe_node(t_ast *left_node, t_token_array *array, t_parse_helper *helper, char **envp, int *exit_status)
{
	helper->node->type = NODE_PIPE;
	helper->node->u_data.pipe.left = ft_calloc(1, sizeof(t_ast));
	if (!helper->node->u_data.pipe.left)
	{
		*exit_status = 1;
		return (1);
	}
	*(helper->node->u_data.pipe.left) = *left_node;
	helper->node->u_data.pipe.right = ft_calloc(1, sizeof(t_ast));
	if (!helper->node->u_data.pipe.right)
	{
		free(helper->node->u_data.pipe.left);
		*exit_status = 1;
		return (1);
	}
	if (parse_pipe(array, helper, envp, exit_status))
	{
		free(helper->node->u_data.pipe.left);
		free(helper->node->u_data.pipe.right);
		*exit_status = 1;
		return (1);
	}
	return (0);
}
