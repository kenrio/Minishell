/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:50:56 by keishii           #+#    #+#             */
/*   Updated: 2025/03/29 13:40:49 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirect	*make_redirect_struct(void);
static void			set_redirect_type(t_redirect *redirect, t_token *token);
static int			set_redirect_file(t_redirect *redirect, t_token_array *array, t_parse_helper *helper, int *exit_status);
static void			add_redirect_to_list(t_ast *node, t_redirect *redirect);

int	add_redirect(t_token_array *array, t_parse_helper *helper, int *exit_status)
{
	t_redirect	*redirect;
	t_token		*token;

	token = &(array->tokens[helper->index]);
	redirect = make_redirect_struct();
	if (!redirect)
		return (1);
	set_redirect_type(redirect, token);
	if (set_redirect_file(redirect, array, helper, exit_status))
		return (1);
	add_redirect_to_list(helper->node, redirect);
	return (0);
}

static t_redirect	*make_redirect_struct(void)
{
	t_redirect	*redirect;

	redirect = ft_calloc(1, sizeof(t_redirect));
	if (!redirect)
		return (NULL);
	return (redirect);
}

static void	set_redirect_type(t_redirect *redirect, t_token *token)
{
	if (token->token_type == REDIRECT_OUT)
		redirect->type = R_OUT;
	else if (token->token_type == REDIRECT_IN)
		redirect->type = R_IN;
	else if (token->token_type == REDIRECT_APPEND)
		redirect->type = R_OUT_APPEND;
	else if (token->token_type == REDIRECT_HEREDOC)
		redirect->type = R_HEREDOC;
}

static int	set_redirect_file(t_redirect *redirect, t_token_array *array, t_parse_helper *helper, int *exit_status)
{
	helper->index++;
	if (helper->index >= array->len)
	{
		free(redirect);
		return (*exit_status = 1, 1);
	}
	redirect->file_name = dq_expand_doller(array->tokens[helper->index].token,
			helper->node->u_data.cmd.envp, exit_status);
	if (!redirect->file_name)
	{
		free(redirect);
		return (*exit_status = 1, 1);
	}
	helper->index++;
	return (0);
}

static void	add_redirect_to_list(t_ast *node, t_redirect *redirect)
{
	t_redirect	*current;

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
}
