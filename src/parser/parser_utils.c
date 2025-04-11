/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:52:40 by keishii           #+#    #+#             */
/*   Updated: 2025/04/11 16:42:06 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd_args(t_ast *node, int count)
{
	while (--count >= 0)
		free(node->u_data.cmd.argv[count]);
	free(node->u_data.cmd.argv);
	// free(node->u_data.cmd.name);
}

int	is_redirect(t_token *token)
{
	return (token->token_type == REDIRECT_OUT
		|| token->token_type == REDIRECT_IN
		|| token->token_type == REDIRECT_APPEND
		|| token->token_type == REDIRECT_HEREDOC);
}
