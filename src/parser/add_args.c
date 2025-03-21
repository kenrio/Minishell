/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:30 by keishii           #+#    #+#             */
/*   Updated: 2025/03/21 23:47:45 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_args(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	int	i;

	i = 1;
	while (*pos < array->len && array->tokens[*pos].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[*pos]))
		{
			if (add_redirect(node, array, pos, exit_status))
			{
				free_cmd_args(node, i);
				return (1);
			}
		}
		else
		{
			node->u_data.cmd.argv[i] = ft_strdup(array->tokens[*pos].token);
			if (!node->u_data.cmd.argv[i])
			{
				free_cmd_args(node, i);
				*exit_status = 1;
				return (1);
			}
			i++;
			(*pos)++;
		}
	}
	node->u_data.cmd.argv[i] = NULL;
	return (0);
}
