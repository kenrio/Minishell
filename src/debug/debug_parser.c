/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:56:02 by keishii           #+#    #+#             */
/*   Updated: 2025/04/28 12:48:18 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	debug_print_ast(t_ast *node, int depth)
// {
// 	int			i;
// 	int			j;
// 	t_redirect	*redirect;

// 	printf("\n");
// 	printf("----------------------------------\n");


// 	if (!node)
// 		return ;
// 	i = 0;
// 	while (i++ < depth)
// 		printf("  ");
// 	if (node->type == NODE_CMD)
// 	{
// 		// output command_name
// 		if (node->u_data.cmd.name)
// 			printf("CMD_NAME: %s\n", node->u_data.cmd.name);
// 		else
// 			printf("CMD_NAME: (null)\n");

			
// 		// depth
// 		i = 0;
// 		while (i++ < depth)
// 			printf("  ");	

			
// 		// output command path
// 		printf("  path: %s\n", node->u_data.cmd.path);


// 		// output arg
// 		j = 1;
// 		while (node->u_data.cmd.argv && node->u_data.cmd.argv[j])
// 		{
// 			i = 0;
// 			while (i++ < depth)
// 				printf("  ");
// 			printf("  argv[%d]: %s\n", j, node->u_data.cmd.argv[j]);
// 			j++;
// 		}

// 		// output redirect
// 		redirect = node->u_data.cmd.redirects;
// 		while (redirect)
// 		{
// 			i = 0;
// 			while (i++ < depth)
// 				printf("  ");
// 			printf("  REDIRECT: ");
// 			if (redirect->type == R_OUT)
// 				printf(">");
// 			else if (redirect->type == R_IN)
// 				printf("<");
// 			else if (redirect->type == R_OUT_APPEND)
// 				printf(">>");
// 			else if (redirect->type == R_HEREDOC)
// 				printf("<<");
// 			printf(" %s\n", redirect->file_name);
// 			redirect = redirect->next;
// 		}
// 	}
// 	else if (node->type == NODE_PIPE)
// 	{
// 		printf("PIPE:\n");
// 		debug_print_ast(node->u_data.pipe.left, depth + 1);
// 		debug_print_ast(node->u_data.pipe.right, depth + 1);
// 	}
// 	else
// 	{
// 		printf("UNKNOWN NODE TYPE: %d\n", node->type);
// 	}


// 	printf("----------------------------------\n");
// 	printf("\n");
// }
