/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:30:31 by keishii           #+#    #+#             */
/*   Updated: 2025/03/31 19:39:56 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_pipe(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	printf("DEBUG: parse_pipe start, index=%d\n", helper->index);
	if (parse_cmd(array, helper, envl, exit_status))
	{
		printf("DEBUG: parse_cmd failed\n");
		return (*exit_status = 1, 1);
	}
	printf("DEBUG: After parse_cmd, index=%d, len=%d\n", helper->index, array->len);
	if (helper->index < array->len
		&& array->tokens[helper->index].token_type == PIPE)
	{
		printf("DEBUG: Found PIPE token at index %d\n", helper->index);
		helper->index++;
		if (make_pipe_node(array, helper, envl, exit_status))
			return (*exit_status = 1, 1);
		return (0);
	}
	printf("DEBUG: parse_pipe end, index=%d\n", helper->index);
	return (0);
}
