/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:44:07 by keishii           #+#    #+#             */
/*   Updated: 2025/03/25 16:32:07 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_empty_cmd_node(t_ast *node, int *exit_status);
static int	set_cmd_name(t_ast *node, t_token_array *array, t_parser_helper *p_help, int *exit_status);
static int	find_cmd_name(t_ast *node, t_token_array *array,
				int *pos, int *exit_status);
static int	allocate_argv_mem(t_ast *node, int arg_count, int *exit_status);
static int	set_argv0(t_ast *node, int *exit_status);

int	make_cmd_node(t_ast *node, t_token_array *array, t_parser_helper *p_help, char **envp, int *exit_status)
{
	node->type = NODE_CMD;
	node->u_data.cmd.redirects = NULL;
	node->u_data.cmd.envp = envp;
	if (p_help->arg_count == 0)
		return (make_empty_cmd_node(node, exit_status));
	if (set_cmd_name(node, array, p_help, exit_status))
		return (1);
	node->u_data.cmd.path = get_cmd_path(envp, node->u_data.cmd.name);
	return (add_args(node, array, &p_help->index, exit_status));
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

static int	set_cmd_name(t_ast *node, t_token_array *array, t_parser_helper *p_help, int *exit_status)
{
	if (find_cmd_name(node, array, &p_help->index, exit_status))
		return (1);
	if (allocate_argv_mem(node, p_help->arg_count, exit_status))
		return (1);
	if (set_argv0(node, exit_status))
		return (1);
	p_help->index++;
	return (0);
}

static int	find_cmd_name(t_ast *node, t_token_array *array,
	int *pos, int *exit_status)
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
			// node->u_data.cmd.name = ft_strdup(array->tokens[*pos].token);
			node->u_data.cmd.name
				= dq_expand_doller(array->tokens[*pos].token, node->u_data.cmd.envp, exit_status);
			break ;
		}
	}
	if ((!node->u_data.cmd.name))
	{
		*exit_status = 1;
		return (1);
	}
	return (0);
}

static int	allocate_argv_mem(t_ast *node, int arg_count, int *exit_status)
{
	node->u_data.cmd.argv = ft_calloc(arg_count + 1, sizeof(char *));
	if (!node->u_data.cmd.argv)
	{
		free(node->u_data.cmd.name);
		*exit_status = 1;
		return (1);
	}
	return (0);
}

static int	set_argv0(t_ast *node, int *exit_status)
{
	node->u_data.cmd.argv[0] = ft_strdup(node->u_data.cmd.name);
	if (!node->u_data.cmd.argv[0])
	{
		free(node->u_data.cmd.argv);
		free(node->u_data.cmd.name);
		*exit_status = 1;
		return (1);
	}
	return (0);
}
