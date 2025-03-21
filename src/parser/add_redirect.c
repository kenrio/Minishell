/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:50:56 by keishii           #+#    #+#             */
/*   Updated: 2025/03/21 23:52:06 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_redirect(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	t_ridirect	*redirect;
	t_ridirect	*current;
	t_token		*token;

	token = &(array->tokens[*pos]);
	redirect = ft_calloc(1, sizeof(t_ridirect));
	if (!redirect)
	{
		*exit_status = 1;
		return (1);
	}
	if (token->token_type == REDIRECT_OUT)
		redirect->type = R_OUT;
	else if (token->token_type == REDIRECT_IN)
		redirect->type = R_IN;
	else if (token->token_type == REDIRECT_APPEND)
		redirect->type = R_OUT_APPEND;
	else if (token->token_type == REDIRECT_HEREDOC)
		redirect->type = R_HEREDOC;
	(*pos)++;
	if (*pos >= array->len)
	{
		free(redirect);
		*exit_status = 258;
		return (1);
	}
	redirect->file_name = ft_strdup(array->tokens[*pos].token);
	if (!redirect->file_name)
	{
		free(redirect);
		*exit_status = 1;
		return (1);
	}
	redirect->next = NULL;
	if (!node->u_data.cmd.redirects)
		node->u_data.cmd.redirects = redirect;
	else
	{
		current = node->u_data.cmd.redirects;
		while (current->next)
			current = current->next;
		current->next = redirect;
	}
	(*pos)++;
	return (0);
}
