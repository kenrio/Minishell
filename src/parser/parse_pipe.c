/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:30:31 by keishii           #+#    #+#             */
/*   Updated: 2025/03/30 20:52:58 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_token_array *array, t_parse_helper *helper, char **envp, int *exit_status)
{
	if (parse_cmd(array, helper, envp, exit_status))
		return (*exit_status = 1, 1);
	if (helper->index < array->len && array->tokens[helper->index].token_type == PIPE)
	{
		helper->index++;
		if (make_pipe_node(array, helper, envp, exit_status))
			return (*exit_status = 1, 1);
		return (0);
	}
	return (0);
}
