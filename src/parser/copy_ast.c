/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 18:39:03 by keishii           #+#    #+#             */
/*   Updated: 2025/04/12 23:03:34 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redirect	*copy_redirects(t_redirect *src);
static int			copy_cmd_node(t_ast *dst, t_ast *src, int *exit_status);
static char			**copy_envp(char **src);
static void			free_redirects(t_redirect *redirect);
static void			free_2d_array(char **arr, size_t count);

t_ast *copy_ast(t_ast *src, int *exit_status)
{
	t_ast	*copy;

	int		j;

	copy = ft_calloc(1, sizeof(t_ast));
	if (!copy)
		return (*exit_status = 1, NULL);
	copy->type = src->type;
	if (src->type == NODE_CMD)
	{
		if (copy_cmd_node(copy, src, exit_status))
		{
			free_ast(copy);
			return (*exit_status = 1, NULL);
		}
	}
	else if (src->type == NODE_PIPE)
	{
		copy->u_data.pipe.left = ast_copy(src->u_data.pipe.left, exit_status);
		copy->u_data.pipe.right = ast_copy(src->u_data.pipe.right, exit_status);
		if (!copy->u_data.pipe.left || !copy->u_data.pipe.right)
		{
			free_ast(copy);
			return (*exit_status = 1, NULL);
		}
	}
	return (copy);
}

static int	copy_cmd_node(t_ast *dst, t_ast *src, int *exit_status)
{
	int		i;
	int		j;

	dst->u_data.cmd.name = ft_strdup(src->u_data.cmd.name);
	if (!dst->u_data.cmd.name)
		return (*exit_status = 1, 1);
	i = 0;
	while (src->u_data.cmd.argv && src->u_data.cmd.argv[i])
		i++;
	dst->u_data.cmd.argv = ft_calloc(i + 1, sizeof(char *));
	if (!dst->u_data.cmd.argv)
		return (free(dst->u_data.cmd.name), *exit_status, 1);
	j = 0;
	while(j < i)
	{
		dst->u_data.cmd.argv[j] = ft_strdup(src->u_data.cmd.argv[j]);
		if (!dst->u_data.cmd.argv[j])
		{
			free_2d_array(dst->u_data.cmd.argv, j);
			free(dst->u_data.cmd.name);
			return (*exit_status = 1, 1);
		}
		j++;
	}
	dst->u_data.cmd.envp = copy_envp(src->u_data.cmd.envp);
	dst->u_data.cmd.redirects = copy_redirects(src->u_data.cmd.redirects);
	if (!dst->u_data.cmd.envp || !dst->u_data.cmd.redirects)
		return (*exit_status = 1, 1);
	dst->u_data.cmd.stp = src->u_data.cmd.stp;
	return (0);
}

static t_redirect	*copy_redirects(t_redirect *src)
{
	t_redirect *new_head;
	t_redirect **curr;

	new_head = NULL;
	curr = &new_head;
	while (src)
	{
		*curr = ft_calloc(1, sizeof(t_redirect));
		if (!(*curr))
		{
			free_redirects(new_head);
			return (NULL);
		}
		(*curr)->type = src->type;
		(*curr)->file_name = ft_strdup(src->file_name);
		if (!(*curr)->file_name)
		{
			free_redirects(new_head);
			return (NULL);
		}
		(*curr)->next = NULL;
		curr = &((*curr)->next);
		src = src->next;
	}
	return (new_head);
}

static char	**copy_envp(char **src)
{
	size_t	len;
	size_t	i;
	char	**dst;

	if (!src)
		return (NULL);
	len = 0;
	while (src[len])
		len++;
	dst = ft_calloc(len + 1, sizeof(char *));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
		{
			free_2d_array(dst, i);
			return (NULL);
		}
		i++;
	}
	dst[len] = NULL;
	return (dst);
}

static void	free_redirects(t_redirect *redirect)
{
	t_redirect *tmp;

	while (redirect)
	{
		tmp = redirect->next;
		free(redirect->file_name);
		free(redirect);
		redirect = tmp;
	}
}

static void	free_2d_array(char **arr, size_t count)
{
	if (!arr)
		return ;
	while (count-- > 0)
		free(arr[count]);
	free(arr);
}
