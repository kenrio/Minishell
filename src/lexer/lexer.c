/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:01:33 by keishii           #+#    #+#             */
/*   Updated: 2025/02/25 20:18:14 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_split(char *input_line, t_token_list *token_list);

int	lexer(char *input_line, t_token_list *token_list)
{
	printf("input_line: %s\n", input_line);
	lexer_split(input_line, token_list);
	return (0);
}

static int	lexer_split(char *input_line, t_token_list *token_list)
{
	int				i;
	t_lexer_flag	lexer_flag;

	i = 0;
	lexer_flag.in_squote = false;
	lexer_flag.in_dquote = false;
	token_list->num = 0;
	while (ft_isspace(input_line[i]))
		i++;
	printf("input_line[%d]: %c\n", i, input_line[i]);
	while (input_line[++i])
	{
		if (input_line[i] == '\'' && !lexer_flag.in_squote)
		{
			printf("input_line[%d]: %c\n", i, input_line[i]);
			lexer_flag.in_squote = true;
			i++;
			while (input_line[i] != '\'')
			{
				i++;
			}
			printf("input_line[%d]: %c\n", i, input_line[i]);
			lexer_flag.in_squote = false;
			token_list->num++;
			break ;
		}
		else if (input_line[i] == '"' && !lexer_flag.in_dquote)
		{
			printf("input_line[%d]: %c\n", i, input_line[i]);
			lexer_flag.in_dquote = true;
			i++;
			while (input_line[i] != '"')
			{
				i++;
			}
			printf("input_line[%d]: %c\n", i, input_line[i]);
			lexer_flag.in_dquote = false;
			token_list->num++;
			break ;
		}
		else if (input_line[i] == '|')
		{
			token_list->num++;
		}
		else if (input_line[i] == ' ')
		{
			token_list->num++;
		}
	}
	printf("input_line[%d]: %c\n", i, input_line[i]);
	printf("lexer_flag.in_squote: %d\n", lexer_flag.in_squote);
	printf("lexer_flag.in_dquote: %d\n", lexer_flag.in_dquote);
	printf("token_list->num: %d\n", token_list->num);
	return (0);
}
