/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expantion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:54:23 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/19 14:06:57 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	check_split_result(char **split_array)
// {
// 	int	i;

// 	if (!split_array)
// 	{
// 		printf("split_array is NULL\n");
// 		return;
// 	}
// 	i = 0;
// 	while (split_array[i] != NULL)
// 	{
// 		printf("split_array[%d]: \"%s\"\n", i, split_array[i]);
// 		i++;
// 	}
// }

void	check_expand(char **envp, int *stp)
{
	char	*cmd = "echo $USER , $$USER $ $? ,'$USER, \"\'$USER\'\"";

	printf(" origin:  %s\n", cmd);
	printf("cmdline: %s\n", dq_expand_doller(cmd, envp, stp));
	printf("heredoc: %s\n", expand_doller_heredoc(cmd, envp, stp));
}
