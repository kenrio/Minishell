/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:36:56 by keishii           #+#    #+#             */
/*   Updated: 2025/03/21 23:38:45 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token_array *array, int start_pos);

int	parse_cmd(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	int	arg_count;

	if (*pos >= array->len)
		return (1);
	arg_count = count_args(array, *pos);
	return (make_cmd_node(node, array, pos, arg_count, exit_status));
}

static int	count_args(t_token_array *array, int start_pos)
{
	int	i;
	int	arg_count;

	i = start_pos;
	arg_count = 0;
	while (i < array->len && array->tokens[i].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[i]))
		{
			i += 2;
			if (i > array->len)
				break ;
		}
		else
		{
			arg_count++;
			i++;
		}
	}
	return (arg_count);
}
