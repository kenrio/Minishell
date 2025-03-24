/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:36:56 by keishii           #+#    #+#             */
/*   Updated: 2025/03/25 00:16:22 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_args(t_token_array *array, t_parser_helper *p_help);

int	parse_cmd(t_ast *node, t_token_array *array, t_parser_helper *p_help, char **envp, int *exit_status)
{
	if (p_help->index >= array->len)
		return (1);
	count_args(array, p_help);
	return (make_cmd_node(node, array, p_help, envp, exit_status));
}

static int	count_args(t_token_array *array, t_parser_helper *p_help)
{
	int	i;

	i = p_help->index;
	p_help->arg_count = 0;
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
			p_help->arg_count++;
			i++;
		}
	}
	return (p_help->arg_count);
}
