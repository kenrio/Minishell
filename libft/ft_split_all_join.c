/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_all_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:04:31 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/19 12:05:33 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_join_all_split(char **array)
{
	char	*result;
	char	*temp;

	if (!array)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*array)
	{
		temp = result;
		result = ft_strjoin(result, *array);
		if (!result)
			return (NULL);
		free(temp);
		array++;
	}
	return (result);
}
