/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:08:21 by keishii           #+#    #+#             */
/*   Updated: 2025/03/18 13:47:13 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	main_loop(char *input_line, int *exit_status);
static char	*get_input_line(void);



void	check_split_result(char **split_array)
{
	int	i;

	if (!split_array)
	{
		printf("split_array is NULL\n");
		return;
	}
	i = 0;
	while (split_array[i] != NULL)
	{
		printf("split_array[%d]: \"%s\"\n", i, split_array[i]);
		i++;
	}
}






int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	char	*input_line;

	(void)argc;
	(void)argv;
	(void)envp;

	exit_status = 0;
	input_line = NULL;
	exit_status = main_loop(input_line, &exit_status);
	exit(exit_status);
}

static int	main_loop(char *input_line, int *exit_status)
{
	while (1)
	{
		input_line = get_input_line();
		if (!input_line)
			break ;
		*exit_status = lexer(input_line, exit_status);
		free(input_line);
		printf("\nexit_status: %d\n\n", *exit_status);
	}
	return (*exit_status);
}

static char	*get_input_line(void)
{
	char	*input_line;

	input_line = readline(PROMPT);
	if (input_line && ft_strlen(input_line) > 0)
		add_history(input_line);
	return (input_line);
}
