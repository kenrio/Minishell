/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:47:30 by keishii           #+#    #+#             */
/*   Updated: 2025/04/11 16:42:11 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_arg_value(t_token_array *array, t_parse_helper *helper,
				int arg_index, int *exit_status);

int	add_args(t_token_array *array, t_parse_helper *helper, int *exit_status)
{
	int	arg_index;

	arg_index = 1;
	while (helper->index < array->len
		&& array->tokens[helper->index].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[helper->index]))
		{
			if (add_redirect(array, helper, exit_status))
			{
				free_cmd_args(helper->node, arg_index);
				helper->node->u_data.cmd.argv = NULL;
				// helper->node->u_data.cmd.name = NULL;
				return (1);
			}
		}
		else
		{
			if (add_arg_value(array, helper, arg_index, exit_status))
				return (1);
			arg_index++;
		}
	}
	helper->node->u_data.cmd.argv[arg_index] = NULL;
	return (0);
}

static int	add_arg_value(t_token_array *array, t_parse_helper *helper,
				int arg_index, int *exit_status)
{
	helper->node->u_data.cmd.argv[arg_index]
		= dq_expand_doller(array->tokens[helper->index].token,
			helper->node->u_data.cmd.envp, exit_status);
	if (!helper->node->u_data.cmd.argv[arg_index])
		return (free_cmd_args(helper->node, arg_index), 1);
	helper->index++;
	return (0);
}
