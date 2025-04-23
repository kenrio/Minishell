/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_destroy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 11:28:25 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/19 11:33:22 by tishihar         ###   ########.fr       */
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
