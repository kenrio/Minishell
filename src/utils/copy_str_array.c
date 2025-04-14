/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_str_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 02:27:40 by keishii           #+#    #+#             */
/*   Updated: 2025/04/15 02:28:11 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_str_array(char ***dst, char **src)
{
	int	i;

	i = 0;
	if (!src)
		return (1);
	while (src && src[i])
		i++;
	*dst = ft_calloc(i + 1, sizeof(char *));
	if (!(*dst))
		return (1);
	i = 0;
	while (src[i])
	{
		(*dst)[i] = ft_strdup(src[i]);
		if (!(*dst)[i])
		{
			free_str_array((*dst));
			return (1);
		}
		i++;
	}
	return (0);
}
