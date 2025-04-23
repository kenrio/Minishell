/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keishii <keishii@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:28:25 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/23 19:51:25 by keishii          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_destroy_split(char **array)
{
	char	**origin;

	if (!array)
		return ;
	origin = array;
	while (*array)
	{
		free(*array);
		array++;
	}
	free(origin);
}
