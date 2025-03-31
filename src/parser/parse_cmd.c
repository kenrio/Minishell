/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:36:56 by keishii           #+#    #+#             */
/*   Updated: 2025/03/31 13:28:45 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token_array *array, t_parse_helper *helper);

int	parse_cmd(t_token_array *array, t_parse_helper *helper, t_envl *envl, int *exit_status)
{
	if (helper->index >= array->len)
		return (1);
	count_args(array, helper);
	return (make_cmd_node(array, helper, envl, exit_status));
}

static int	count_args(t_token_array *array, t_parse_helper *helper)
{
	int	i;

	i = helper->index;
	helper->arg_count = 0;
	while (i < array->len && array->tokens[i].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[i]))
		{
			if (i > array->len)
				break ;
			i += 2;
		}
		else
		{
			helper->arg_count++;
			i++;
		}
	}
	return (helper->arg_count);
}
