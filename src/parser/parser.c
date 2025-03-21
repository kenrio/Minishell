/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:53:17 by keishii           #+#    #+#             */
/*   Updated: 2025/03/21 22:09:18 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_ast(t_ast *node, t_token_array *array, int *pos, int *exit_status);
static int	parse_pipe(t_ast *node, t_token_array *array, int *pos, int *exit_status);
static int	make_pipe_node(t_ast *node, t_ast *left_node, t_token_array *array, int *pos, int *exit_status);
static int	parse_cmd(t_ast *node, t_token_array *array, int *pos, int *exit_status);
static int	count_args(t_token_array *array, int start_pos);
static int	make_cmd_node(t_ast *node, t_token_array *array, int *pos, int arg_count, int *exit_status);
static int	make_empty_cmd_node(t_ast *node, int *exit_status);
static int	set_cmd_name(t_ast *node, t_token_array *array, int *pos, int arg_count, int *exit_status);
static int	add_args(t_ast *node, t_token_array *array, int *pos, int *exit_status);
static void	free_cmd_args(t_ast *node, int count);
static int	is_redirect(t_token *token);
static int	add_redirect(t_ast *node, t_token_array *array, int *pos, int *exit_status);
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
	// printf("pos: %d\n", pos);
	printf("\n");
	print_ast(ast_node, 1);
	printf("\n");
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
	if (parse_pipe(node, array, pos, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	return (0);
}

static int	parse_pipe(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	t_ast	left_node;

	if (parse_cmd(&left_node, array, pos, exit_status))
	{
		*exit_status = 1;
		return (1);
	}
	if (*pos < array->len && array->tokens[*pos].token_type == PIPE)
	{
		(*pos)++;
		if (make_pipe_node(node, &left_node, array, pos, exit_status))
		{
			*exit_status = 1;
			return (1);
		}
		return (0);
	}
	*node = left_node;
	return (0);
}

static int	make_pipe_node(t_ast *node, t_ast *left_node, t_token_array *array, int *pos, int *exit_status)
{
	node->type = NODE_PIPE;
	node->u_data.pipe.left = ft_calloc(1, sizeof(t_ast));
	if (!node->u_data.pipe.left)
	{
		*exit_status = 1;
		return (1);
	}
	*(node->u_data.pipe.left) = *left_node;
	node->u_data.pipe.right = ft_calloc(1, sizeof(t_ast));
	if (!node->u_data.pipe.right)
	{
		free(node->u_data.pipe.left);
		*exit_status = 1;
		return (1);
	}
	if (parse_pipe(node->u_data.pipe.right, array, pos, exit_status))
	{
		free(node->u_data.pipe.left);
		free(node->u_data.pipe.right);
		*exit_status = 1;
		return (1);
	}
	return (0);
}

static int	parse_cmd(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	int	arg_count;

	if (*pos >= array->len)
		return (1);
	arg_count = count_args(array, *pos);
	return (make_cmd_node(node, array, pos, arg_count, exit_status));
}

static int	count_args(t_token_array *array, int start_pos)
{
	int	i;
	int	arg_count;

	i = start_pos;
	arg_count = 0;
	while (i < array->len && array->tokens[i].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[i]))
		{
			i += 2;
			if (i > array->len)
				break ;
		}
		else
		{
			arg_count++;
			i++;
		}
	}
	return (arg_count);
}

static int	make_cmd_node(t_ast *node, t_token_array *array, int *pos, int arg_count, int *exit_status)
{
	node->type = NODE_CMD;
	node->u_data.cmd.redirects = NULL;
	if (arg_count == 0)
		return (make_empty_cmd_node(node, exit_status));
	if (set_cmd_name(node, array, pos, arg_count, exit_status))
		return (1);
	return (add_args(node, array, pos, exit_status));
}

static int	make_empty_cmd_node(t_ast *node, int *exit_status)
{
	node->u_data.cmd.name = ft_strdup("");
	if (!node->u_data.cmd.name)
	{
		*exit_status = 1;
		return (1);
	}
	node->u_data.cmd.argv = ft_calloc(1, sizeof(char *));
	if (!node->u_data.cmd.argv)
	{
		free(node->u_data.cmd.argv);
		*exit_status = 1;
		return (1);
	}
	node->u_data.cmd.argv[0] = NULL;
	return (0);
}

static int	set_cmd_name(t_ast *node, t_token_array *array, int *pos, int arg_count, int *exit_status)
{
	while (*pos < array->len && array->tokens[*pos].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[*pos]))
		{
			if (add_redirect(node, array, pos, exit_status))
				return (1);
		}
		else
		{
			node->u_data.cmd.name = ft_strdup(array->tokens[*pos].token);
			break ;
		}
	}
	if ((!node->u_data.cmd.name))
	{
		*exit_status = 1;
		return (1);
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
		free(node->u_data.cmd.argv);
		free(node->u_data.cmd.name);
		*exit_status = 1;
		return (1);
	}
	(*pos)++;
	return (0);
}

static int	add_args(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	int	i;

	i = 1;
	while (*pos < array->len && array->tokens[*pos].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[*pos]))
		{
			if (add_redirect(node, array, pos, exit_status))
			{
				free_cmd_args(node, i);
				return (1);
			}
		}
		else
		{
			node->u_data.cmd.argv[i] = ft_strdup(array->tokens[*pos].token);
			if (!node->u_data.cmd.argv[i])
			{
				free_cmd_args(node, i);
				*exit_status = 1;
				return (1);
			}
			i++;
			(*pos)++;
		}
	}
	node->u_data.cmd.argv[i] = NULL;
	return (0);
}

static void	free_cmd_args(t_ast *node, int count)
{
	while (--count >= 0)
		free(node->u_data.cmd.argv[count]);
	free(node->u_data.cmd.argv);
	free(node->u_data.cmd.name);
}

static int	is_redirect(t_token *token)
{
	return (token->token_type == REDIRECT_OUT
		|| token->token_type == REDIRECT_IN
		|| token->token_type == REDIRECT_APPEND
		|| token->token_type == REDIRECT_HEREDOC);
}

static int	add_redirect(t_ast *node, t_token_array *array, int *pos, int *exit_status)
{
	t_ridirect	*redirect;
	t_ridirect	*current;
	t_token		*token;

	token = &(array->tokens[*pos]);
	redirect = ft_calloc(1, sizeof(t_ridirect));
	if (!redirect)
	{
		*exit_status = 1;
		return (1);
	}
	if (token->token_type == REDIRECT_OUT)
		redirect->type = R_OUT;
	else if (token->token_type == REDIRECT_IN)
		redirect->type = R_IN;
	else if (token->token_type == REDIRECT_APPEND)
		redirect->type = R_OUT_APPEND;
	else if (token->token_type == REDIRECT_HEREDOC)
		redirect->type = R_HEREDOC;
	(*pos)++;
	if (*pos >= array->len)
	{
		free(redirect);
		*exit_status = 258;
		return (1);
	}
	redirect->file_name = ft_strdup(array->tokens[*pos].token);
	if (!redirect->file_name)
	{
		free(redirect);
		*exit_status = 1;
		return (1);
	}
	redirect->next = NULL;
	if (!node->u_data.cmd.redirects)
		node->u_data.cmd.redirects = redirect;
	else
	{
		current = node->u_data.cmd.redirects;
		while (current->next)
			current = current->next;
		current->next = redirect;
	}
	(*pos)++;
	return (0);
}

static void	print_ast(t_ast *node, int depth)
{
	int			i;
	int			j;
	t_ridirect	*redirect;

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
		print_ast(node->u_data.pipe.left, depth + 1);
		print_ast(node->u_data.pipe.right, depth + 1);
	}
}
