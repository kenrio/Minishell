/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:24:32 by keishii           #+#    #+#             */
/*   Updated: 2025/03/21 23:28:32 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_ast(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	if (parse_pipe(node, array, pos, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	return (0);
}
