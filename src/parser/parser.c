/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:53:17 by keishii           #+#    #+#             */
/*   Updated: 2025/03/19 20:29:06 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_ast(t_ast *node, t_token_array *array, int *pos, int *exit_status);
static int	make_pipeline_node(t_ast *node, t_token_array *array, int *pos, int *exit_status);
static int	make_command_node(t_ast *node, t_token_array *array, int *pos, int *exit_status);
static void	print_ast(t_ast *node, int depth);

int	parser(t_ast *ast_node, t_token_array *token_array, int *exit_status)
{
	int	pos;

	pos = 0;
	if (make_ast(ast_node, token_array, &pos, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	printf("pos: %d\n", pos);
	print_ast(ast_node, 5);
	if (pos != token_array->len)
	{
		// free_ast(ast_node);
		*exit_status = 258;
		return (*exit_status);
	}
	return (*exit_status);
}

static int	make_ast(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	if (make_pipeline_node(node, array, pos, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	return (0);
}

static int	make_pipeline_node(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	t_ast	left_node;

	if (make_command_node(&left_node, array, pos, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	if (*pos < array->len && array->tokens[*pos].token_type == PIPE)
	{
		(*pos)++;
		node->type = NODE_PIPE;
		node->u_data.pipe.left = ft_calloc(1, sizeof(t_ast));
		if (!node->u_data.pipe.left)
		{
			*exit_status = 1;
			return (1);
		}
		*(node->u_data.pipe.left) = left_node;
		node->u_data.pipe.right = ft_calloc(1, sizeof(t_ast));
		if (!node->u_data.pipe.right)
		{
			free(node->u_data.pipe.left);
			*exit_status = 1;
			return (1);
		}
		if (make_pipeline_node(node->u_data.pipe.right, array, pos, exit_status))
		{
			free(node->u_data.pipe.left);
			free(node->u_data.pipe.right);
			*exit_status = 1;
			return (1);
		}
		return (0);
	}
	*node = left_node;
	return (0);
}

static int	make_command_node(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	int	i;
	int	arg_count;

	if (*pos >= array->len)
		return (1);
	node->type = NODE_CMD;
	node->u_data.cmd.name = ft_strdup(array->tokens[*pos].token);
	if (!node->u_data.cmd.name)
	{
		*exit_status = 1;
		return (1);
	}
	arg_count = 1;
	i = *pos + 1;
	while (i < array->len && array->tokens[i].token_type != PIPE)
	{
		arg_count++;
		i++;
	}
	node->u_data.cmd.argv = ft_calloc(arg_count + 1, sizeof(char *));
	if (!node->u_data.cmd.argv)
	{
		free(node->u_data.cmd.name);
		*exit_status = 1;
		return (1);
	}
	node->u_data.cmd.argv[0] = ft_strdup(node->u_data.cmd.name);
	if (!node->u_data.cmd.argv[0])
	{
		free(node->u_data.cmd.name);
		free(node->u_data.cmd.argv);
		*exit_status = 1;
		return (1);
	}
	i = 1;
	(*pos)++;
	while (*pos < array->len && array->tokens[*pos].token_type != PIPE)
	{
		node->u_data.cmd.argv[i] = ft_strdup(array->tokens[*pos].token);
		if (!node->u_data.cmd.argv[i])
		{
			while (--i >= 0)
				free(node->u_data.cmd.argv[i]);
			free(node->u_data.cmd.argv);
			free(node->u_data.cmd.name);
			*exit_status = 1;
			return (1);
		}
		i++;
		(*pos)++;
	}
	node->u_data.cmd.argv[i] = NULL;
	return (0);
}

static void	print_ast(t_ast *node, int depth)
{
	int	i;
	int	j;

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
		while (node->u_data.cmd.argv[j])
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
	}
	else if (node->type == NODE_PIPE)
	{
		printf("PIPE\n");
		print_ast(node->u_data.pipe.left, depth + 1);
		print_ast(node->u_data.pipe.right, depth + 1);
	}
}
