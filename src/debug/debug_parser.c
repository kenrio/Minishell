/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:56:02 by keishii           #+#    #+#             */
/*   Updated: 2025/03/24 18:50:23 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_print_ast(t_ast *node, int depth)
{
	int			i;
	int			j;
	t_redirect	*redirect;

	i = 0;
	if (!node)
		return ;
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (node->type == NODE_CMD)
	{
		printf("CMD: %s\n", node->u_data.cmd.name);
		j = 1;
		while (node->u_data.cmd.argv && node->u_data.cmd.argv[j])
		{
			i = 0;
			while (i < depth)
			{
				printf("  ");
				i++;
			}
			printf("  argv[%d]: %s\n", j, node->u_data.cmd.argv[j]);
			j++;
		}
		redirect = node->u_data.cmd.redirects;
		while (redirect)
		{
			i = 0;
			while (i < depth)
			{
				printf("  ");
				i++;
			}
			printf("  REDIRECT: ");
			if (redirect->type == R_OUT)
				printf(">");
			else if (redirect->type == R_IN)
				printf("<");
			else if (redirect->type == R_OUT_APPEND)
				printf(">>");
			else if (redirect->type == R_HEREDOC)
				printf("<<");
			printf(" %s\n", redirect->file_name);
			redirect = redirect->next;
		}
	}
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE\n");
		debug_print_ast(node->u_data.pipe.left, depth + 1);
		debug_print_ast(node->u_data.pipe.right, depth + 1);
	}
}
