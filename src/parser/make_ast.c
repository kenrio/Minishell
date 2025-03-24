/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:24:32 by keishii           #+#    #+#             */
/*   Updated: 2025/03/24 21:15:43 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_ast(t_ast *node, t_token_array *array, t_parser_helper *p_helper, char **envp, int *exit_status)
{
	if (parse_pipe(node, array, p_helper, envp, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	return (0);
}
