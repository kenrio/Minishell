/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:00:51 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/24 03:27:25 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			len;
	const char	*curr;

	len = ft_strlen(s);
	curr = s + len;
	while (s <= curr)
	{
		if (*curr == (char)c)
			return ((char *)curr);
		curr--;
	}
	return (NULL);
}

/*
#include <string.h>
char	*ft_strrchr(const char *str, int c)
{	
	return (strrchr(str, c));
}
//*/
