/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe_node.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:32:34 by keishii           #+#    #+#             */
/*   Updated: 2025/03/24 21:17:57 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_pipe_node(t_ast *node, t_ast *left_node, t_token_array *array, t_parser_helper *p_help, char **envp, int *exit_status)
{
	node->type = NODE_PIPE;
	node->u_data.pipe.left = ft_calloc(1, sizeof(t_ast));
	if (!node->u_data.pipe.left)
	{
		*exit_status = 1;
		return (1);
	}
	*(node->u_data.pipe.left) = *left_node;
	node->u_data.pipe.right = ft_calloc(1, sizeof(t_ast));
	if (!node->u_data.pipe.right)
	{
		free(node->u_data.pipe.left);
		*exit_status = 1;
		return (1);
	}
	if (parse_pipe(node->u_data.pipe.right, array, p_help, envp, exit_status))
	{
		free(node->u_data.pipe.left);
		free(node->u_data.pipe.right);
		*exit_status = 1;
		return (1);
	}
	return (0);
}
