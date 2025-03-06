/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:01:33 by keishii           #+#    #+#             */
/*   Updated: 2025/03/06 13:20:05 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *input_line, int *exit_status)
{
	t_token_list	token_list;
	t_token_state	check_state;

	token_list.token_list = NULL;
	token_list.num = 0;
	count_tokens(input_line, &token_list);
	init_token_state(&check_state);
	while (input_line[check_state.current_index])
	{
		handle_quote(input_line, &check_state);
		check_state.current_index++;
	}
	if (check_state.in_squote || check_state.in_dquote)
	{
		*exit_status = 1;
		return (*exit_status);
	}
	if (token_list.num == 0)
	{
		*exit_status = 0;
		return (*exit_status);
	}
	token_list.token_list
		= (t_token *)malloc(sizeof(t_token) * (token_list.num + 1));
	if (!token_list.token_list)
	{
		*exit_status = 1;
		return (*exit_status);
	}
	*exit_status = tokenize(input_line, &token_list);
	printf("\ntoken_list->num: %d\n", token_list.num);
	printf("\n");
	assign_token_type(&token_list);
	for (int i = 0; i < token_list.num; i++)
	{
		printf("token_list[%d]: %-10s token_type: %d\n",
			i, token_list.token_list[i].token,
			token_list.token_list[i].token_type);
	}
	return (*exit_status);
}
