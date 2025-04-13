/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:36:56 by keishii           #+#    #+#             */
/*   Updated: 2025/04/13 19:12:35 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token_array *array, t_parse_helper *helper);
static int	check_redirect_syntax(t_token_array *array, int *i);

int	parse_cmd(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	if (helper->index >= array->len)
		return (1);
	if (count_args(array, helper) < 0)
	{
		helper->node = NULL;
		return (*exit_status = 2, 1);
	}
	if (make_cmd_node(array, helper, envl, exit_status))
		return (1);
	printf("cmd.path = %s\n", helper->node->u_data.cmd.path);
	return (0);
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
			if (check_redirect_syntax(array, &i))
			{
				helper->arg_count = -1;
				return (-1);
			}
		}
		else if (array->tokens[i].token_type == WORD)
		{
			helper->arg_count++;
			i++;
		}
		// else
		// {
		// 	syntax_error((char *)array->tokens[i].token);
		// 	helper->arg_count = -1;
		// 	return (-1);
		// }
	}
	return (helper->arg_count);
}

static int	check_redirect_syntax(t_token_array *array, int *i)
{
	if (*i + 1 >= array->len)
	{
		syntax_error("newline");
		return (1);
	}
	if (array->tokens[*i + 1].token_type != WORD)
	{
		syntax_error((char *)array->tokens[*i + 1].token);
		return (1);
	}
	// if (*i + 2 < array->len && is_redirect(&array->tokens[*i + 2]))
	// {
	// 	syntax_error(array->tokens[*i + 2].token);
	// 	return (-1);
	// }
	*i += 2;
	return (0);
}
