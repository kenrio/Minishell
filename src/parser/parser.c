/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:53:17 by keishii           #+#    #+#             */
/*   Updated: 2025/03/25 14:58:14 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_ast *ast_node, t_token_array *token_array, char **envp, int *exit_status)
{
	t_parser_helper	p_help;

	p_help.index = 0;
	if (make_ast(ast_node, token_array, &p_help, envp, exit_status))
		return (*exit_status = 1, 1);
	if (p_help.index != token_array->len)
		return (*exit_status = 258, 1);
	return (0);
}
