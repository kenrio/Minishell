/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:52:40 by keishii           #+#    #+#             */
/*   Updated: 2025/04/16 15:52:18 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_args(t_ast *node, int count)
{
	while (--count >= 0)
		free(node->u_data.cmd.argv[count]);
	free(node->u_data.cmd.argv);
}

int	is_redirect(t_token *token)
{
	return (token->token_type == REDIRECT_OUT
		|| token->token_type == REDIRECT_IN
		|| token->token_type == REDIRECT_APPEND
		|| token->token_type == REDIRECT_HEREDOC);
}

int	reset_cmd_node_fields(t_ast *node, t_envl *envl, int *exit_status)
{
	if (node->u_data.cmd.argv)
		free_str_array(node->u_data.cmd.argv);
	if (node->u_data.cmd.envp)
		free_str_array(node->u_data.cmd.envp);
	node->u_data.cmd.envp = make_envp_by_envl(envl);
	if (!node->u_data.cmd.envp)
		return (*exit_status = 1, 1);
	node->u_data.cmd.stp = exit_status;
	if (node->u_data.cmd.redirects)
		free_redirects(node->u_data.cmd.redirects);
	node->u_data.cmd.redirects = NULL;
	return (0);
}
