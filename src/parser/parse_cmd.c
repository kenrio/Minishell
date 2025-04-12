/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:36:56 by keishii           #+#    #+#             */
/*   Updated: 2025/04/12 01:34:08 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token_array *array, t_parse_helper *helper);

int	parse_cmd(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	int	result;

	if (helper->index >= array->len)
		return (1);
	if (count_args(array, helper) < 0)
		return (*exit_status = 2, 1);
	result = make_cmd_node(array, helper, envl, exit_status);
	return (result);
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
			if (i + 1 >= array->len || array->tokens[i + 1].token_type != WORD)
			{
				if (i + 1 >= array->len)
					syntax_error("newline");
				else if (array->tokens[i + 1].token_type != WORD)
					syntax_error((char *)array->tokens[i + 1].token);
				helper->arg_count = -1;
				return (-1);
			}
			if (i + 2 < array->len && is_redirect(&array->tokens[i + 2]))
			{
				syntax_error(array->tokens[i + 2].token);
				helper->arg_count = -1;
				return (-1);
			}
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
