/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:11:03 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/16 21:48:19 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	size_t	strlen_delimiter(char *str, char del);
static	bool	is_match_key(char *str, char *key);
static	void	handle_rm_node(t_envl *lst, t_env_node *prev, t_env_node *curr);

// this file handle env_list.
int	envl_add_node(t_envl *lst, char *value)
{
	char	*key;

	key = ft_substr(value, 0, strlen_delimiter(value, '='));
	if (!key)
		return (1);
	envl_rm_node(lst, key);
	free(key);
	if (envl_push_back(lst, value))
		return (1);
	return (0);
}

// lstをうけとって、keyに一致したノードを削除する関数
int	envl_rm_node(t_envl *lst, char *key)
{
    t_env_node    *curr;
    t_env_node    *prev;

	if (!lst)
		return (1);
	prev = NULL;
    curr = lst->head;
    while (curr)
    {
        if (is_match_key(curr->value, key))
        {
			handle_rm_node(lst, prev, curr);
            return (0);
        }
		prev = curr;
        curr = curr->next;
    }
    return (1);
}

static	void	handle_rm_node(t_envl *lst, t_env_node *prev, t_env_node *curr)
{
	if (prev == NULL)
		lst->head = curr->next;
	else
		prev->next = curr->next;
	if (curr == lst->tail)
		lst->tail = prev;
	free(curr->value);
	free(curr);
	lst->count -= 1;
}

static	bool	is_match_key(char *str, char *key)
{
	size_t	len;
	len = ft_strlen(key);

	return
	(
	ft_strncmp(str, key, len) == 0
	&& str[len] == '='
	);
}

static	size_t	strlen_delimiter(char *str, char del)
{
	size_t	count;
	count = 0;
	while (*str && *str != del)
	{
		str++;
		count++;
	}
	return (count);
}
