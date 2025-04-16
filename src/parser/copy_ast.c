/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:39:03 by keishii           #+#    #+#             */
/*   Updated: 2025/04/16 19:23:45 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_cmd_node(t_ast *dst, t_ast *src);
static int	copy_name(t_ast *dst, t_ast *src);
static int	copy_path(t_ast *dst, t_ast *src);
static int	copy_redirect_list(t_redirect **dst, t_redirect *src);

t_ast	*copy_ast(t_ast *src, int *exit_status)
{
	t_ast	*copy;

	copy = ft_calloc(1, sizeof(t_ast));
	if (!copy)
		return (*exit_status = 1, NULL);
	copy->type = src->type;
	if (src->type == NODE_CMD)
	{
		if (copy_cmd_node(copy, src))
		{
			free_ast(copy);
			return (*exit_status = 1, NULL);
		}
	}
	else if (src->type == NODE_PIPE)
	{
		copy->u_data.pipe.left = copy_ast(src->u_data.pipe.left, exit_status);
		copy->u_data.pipe.right = copy_ast(src->u_data.pipe.right, exit_status);
		if (!copy->u_data.pipe.left || !copy->u_data.pipe.right)
		{
			free_ast(copy);
			return (*exit_status = 1, NULL);
		}
	}
	return (copy);
}

static int	copy_cmd_node(t_ast *dst, t_ast *src)
{
	t_ast	**dst_node;
	t_ast	**src_node;

	dst_node = &dst;
	src_node = &src;
	if (copy_name(*dst_node, *src_node))
		return (1);
	if (copy_path(*dst_node, *src_node))
		return (1);
	if (copy_str_array(&(*dst_node)->u_data.cmd.argv,
			(*src_node)->u_data.cmd.argv))
		return (1);
	if (copy_str_array(&(*dst_node)->u_data.cmd.envp,
			(*src_node)->u_data.cmd.envp))
		return (1);
	if (copy_redirect_list(&(*dst_node)->u_data.cmd.redirects,
			(*src_node)->u_data.cmd.redirects))
		return (1);
	if (src->u_data.cmd.redirects && !dst->u_data.cmd.redirects)
		return (1);
	dst->u_data.cmd.stp = src->u_data.cmd.stp;
	return (0);
}

static int	copy_name(t_ast *dst, t_ast *src)
{
	if (src->u_data.cmd.name)
	{
		dst->u_data.cmd.name = ft_strdup(src->u_data.cmd.name);
		if (!dst->u_data.cmd.name)
			return (1);
	}
	return (0);
}

static int	copy_path(t_ast *dst, t_ast *src)
{
	if (src->u_data.cmd.path)
	{
		dst->u_data.cmd.path = ft_strdup(src->u_data.cmd.path);
		if (!dst->u_data.cmd.path)
			return (1);
	}
	return (0);
}

static int	copy_redirect_list(t_redirect **dst, t_redirect *src)
{
	t_redirect	*new_head;
	t_redirect	**curr;

	new_head = NULL;
	curr = &new_head;
	while (src)
	{
		*curr = ft_calloc(1, sizeof(t_redirect));
		if (!(*curr))
			return (1);
		(*curr)->type = src->type;
		(*curr)->file_name = ft_strdup(src->file_name);
		if (!(*curr)->file_name)
			return (1);
		curr = &(*curr)->next;
		src = src->next;
	}
	*dst = new_head;
	return (0);
}
