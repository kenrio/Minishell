/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:53:17 by keishii           #+#    #+#             */
/*   Updated: 2025/03/31 13:27:25 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_ast *ast_node, t_token_array *token_array, t_envl *envl, int *exit_status)
{
	t_parse_helper	helper;

	helper.index = 0;
	helper.node = ast_node;
	if (make_ast(token_array, &helper, envl, exit_status))
		return (*exit_status = 1, 1);
	if (helper.index != token_array->len)
		return (*exit_status = 2, 1);
	return (0);
}
