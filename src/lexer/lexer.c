/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:01:33 by keishii           #+#    #+#             */
/*   Updated: 2025/02/26 20:28:20 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	lexer_split(char *input_line, t_token_list *token_list);
static void	init_lexer(t_token_list *list, t_lexer_flag *flag);
static void	count_token(char *line, t_token_list *list, t_lexer_flag *flag);

int	lexer(char *input_line)
{
	t_token_list	token_list;

	printf("input_line: %s\n", input_line);
	lexer_split(input_line, &token_list);
	printf("token_list->num: %d\n", token_list.num);
	return (0);
}

static int	lexer_split(char *input_line, t_token_list *token_list)
{
	t_lexer_flag	lexer_flag;

	init_lexer(token_list, &lexer_flag);
	count_token(input_line, token_list, &lexer_flag);
	return (0);
}

static void	init_lexer(t_token_list *list, t_lexer_flag *flag)
{
	list->num = 0;
	flag->in_squote = false;
	flag->in_dquote = false;
	flag->new_token = true;
}

static void	count_token(char *line, t_token_list *list, t_lexer_flag *flag)
{
	int	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (!line[i])
		return ;
	while (line[i])
	{
		if (line[i] == '\'' && !(*flag).in_dquote)
			(*flag).in_squote = !(*flag).in_squote;
		else if (line[i] == '"' && !(*flag).in_squote)
			(*flag).in_dquote = !(*flag).in_dquote;
		if (!(*flag).in_squote && !(*flag).in_dquote)
		{
			if (ft_isspace(line[i]))
				(*flag).new_token = true;
			else if (line[i] == '|' || line[i] == '<' || line[i] == '>')
			{
				if ((*flag).new_token || (i > 0 && (line[i - 1] != line[i])))
					list->num++;
				(*flag).new_token = true;
			}
			else if ((*flag).new_token)
			{
				list->num++;
				(*flag).new_token = false;
			}
		}
		i++;
	}
}
