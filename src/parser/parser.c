/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:53:17 by keishii           #+#    #+#             */
/*   Updated: 2025/03/24 21:35:59 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parser(t_ast *ast_node, t_token_array *token_array, char **envp, int *exit_status)
{
	t_parser_helper	p_help;

	p_help.index = 0;
	if (make_ast(ast_node, token_array, &p_help, envp, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	printf("\n");
	debug_print_ast(ast_node, 1);
	printf("\n");
	if (p_help.index != token_array->len)
	{
		*exit_status = 258;
		return (1);
	}
	return (0);
}
