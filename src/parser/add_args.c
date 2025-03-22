/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:30 by keishii           #+#    #+#             */
/*   Updated: 2025/03/22 14:01:22 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_arg_value(t_ast *node, t_token_array *array, int *pos, int arg_index, int *exit_status);

int	add_args(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	int	arg_index;

	arg_index = 1;
	while (*pos < array->len && array->tokens[*pos].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[*pos]))
		{
			if (add_redirect(node, array, pos, exit_status))
			{
				free_cmd_args(node, arg_index);
				return (1);
			}
		}
		else
		{
			if (add_arg_value(node, array, pos, arg_index, exit_status))
				return (1);
			arg_index++;
		}
	}
	node->u_data.cmd.argv[arg_index] = NULL;
	return (0);
}

static int	add_arg_value(t_ast *node, t_token_array *array, int *pos, int arg_index, int *exit_status)
{
	node->u_data.cmd.argv[arg_index] = ft_strdup(array->tokens[*pos].token);
	if (!node->u_data.cmd.argv[arg_index])
	{
		free_cmd_args(node, arg_index);
		*exit_status = 1;
		return (1);
	}
	(*pos)++;
	return (0);
}
