/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 23:44:07 by keishii           #+#    #+#             */
/*   Updated: 2025/04/06 14:46:44 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	make_empty_cmd_node(t_ast *node, int *exit_status);
static int	set_cmd_name(t_token_array *array, t_parse_helper *helper,
				int *exit_status);
static int	find_cmd_name(t_token_array *array, t_parse_helper *helper,
				int *exit_status);
static int	set_argv0(t_parse_helper *helper, int *exit_status);

int	make_cmd_node(t_token_array *array, t_parse_helper *helper, t_envl *envl,
		int *exit_status)
{
	if (!helper->node)
	{
		helper->node = ft_calloc(1, sizeof(t_ast));
		if (!helper->node)
			return (*exit_status = 1, 1);
	}
	helper->node->type = NODE_CMD;
	helper->node->u_data.cmd.redirects = NULL;
	helper->node->u_data.cmd.envp = make_envp_by_envl(envl);
	helper->node->u_data.cmd.stp = exit_status;
	if (helper->arg_count == 0)
		return (make_empty_cmd_node(helper->node, exit_status));
	if (set_cmd_name(array, helper, exit_status))
		return (1);
	helper->node->u_data.cmd.path = get_cmd_path(helper->node->u_data.cmd.envp,
			helper->node->u_data.cmd.name);
	return (add_args(array, helper, exit_status));
}

static int	make_empty_cmd_node(t_ast *node, int *exit_status)
{
	node->u_data.cmd.name = ft_strdup("");
	if (!node->u_data.cmd.name)
		return (*exit_status = 1, 1);
	node->u_data.cmd.argv = ft_calloc(1, sizeof(char *));
	if (!node->u_data.cmd.argv)
	{
		free(node->u_data.cmd.argv);
		return (*exit_status = 1, 1);
	}
	node->u_data.cmd.argv[0] = NULL;
	return (0);
}

static int	set_cmd_name(t_token_array *array, t_parse_helper *helper,
				int *exit_status)
{
	if (find_cmd_name(array, helper, exit_status))
		return (1);
	if (set_argv0(helper, exit_status))
		return (1);
	helper->index++;
	return (0);
}

static int	find_cmd_name(t_token_array *array, t_parse_helper *helper,
				int *exit_status)
{
	while (helper->index < array->len
		&& array->tokens[helper->index].token_type != PIPE)
	{
		if (is_redirect(&array->tokens[helper->index]))
		{
			if (add_redirect(array, helper, exit_status))
				return (1);
		}
		else
		{
			helper->node->u_data.cmd.name
				= dq_expand_doller(array->tokens[helper->index].token,
					helper->node->u_data.cmd.envp, exit_status);
			break ;
		}
	}
	if ((!helper->node->u_data.cmd.name))
		return (*exit_status = 1, 1);
	return (0);
}

static int	set_argv0(t_parse_helper *helper, int *exit_status)
{
	helper->node->u_data.cmd.argv
		= ft_calloc(helper->arg_count + 1, sizeof(char *));
	if (!helper->node->u_data.cmd.argv)
	{
		free(helper->node->u_data.cmd.name);
		return (*exit_status = 1, 1);
	}
	helper->node->u_data.cmd.argv[0] = ft_strdup(helper->node->u_data.cmd.name);
	if (!helper->node->u_data.cmd.argv[0])
	{
		free(helper->node->u_data.cmd.argv);
		free(helper->node->u_data.cmd.name);
		return (*exit_status = 1, 1);
	}
	return (0);
}
