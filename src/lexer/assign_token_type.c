/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_token_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 21:51:14 by keishii           #+#    #+#             */
/*   Updated: 2025/03/15 15:28:56 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	assign_token_type(t_token_array *array)
{
	int		i;
	t_token	*token;

	i = 0;
	while ((*array).tokens[i].token)
	{
		token = &array->tokens[i];
		if (ft_strcmp(token->token, ">") == 0)
			token->token_type = REDIRECT_OUT;
		else if (ft_strcmp(token->token, "<") == 0)
			token->token_type = REDIRECT_IN;
		else if (ft_strcmp(token->token, ">>") == 0)
			token->token_type = REDIRECT_APPEND;
		else if (ft_strcmp(token->token, "<<") == 0)
			token->token_type = REDIRECT_HEREDOC;
		else if (ft_strcmp(token->token, "|") == 0)
			token->token_type = PIPE;
		else
			token->token_type = WORD;
		i++;
	}
}
