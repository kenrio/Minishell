/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:53:17 by keishii           #+#    #+#             */
/*   Updated: 2025/04/11 18:25:36 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_ast **ast_node, t_token_array *token_array, t_envl *envl,
			int *exit_status)
{
	t_parse_helper	helper;

	helper.index = 0;
	helper.node = NULL;
	if (make_ast(token_array, &helper, envl, exit_status))
	{
		*ast_node = helper.node;
		return (1);
	}
	*ast_node = helper.node;
	if (helper.index != token_array->len)
		return (*exit_status = 2, 1);
	return (0);
}
