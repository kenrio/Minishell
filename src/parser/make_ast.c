/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:24:32 by keishii           #+#    #+#             */
/*   Updated: 2025/03/31 13:47:30 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_ast(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	if (parse_pipe(array, helper, envl, exit_status))
		return (*exit_status = 1, 1);
	return (0);
}
