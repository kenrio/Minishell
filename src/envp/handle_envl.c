/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_envl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:11:03 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/28 15:46:58 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// this file handle env_list.
// lstをうけとって、keyに一致するものが既存の場合は文字列を更新する、ない場合は末尾に追加する関数
int	envl_add_node(t_envl *lst, char *key, char *value)
{
	
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
