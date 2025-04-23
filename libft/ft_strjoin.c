/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:34:06 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/30 23:08:20 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 >= SIZE_MAX - len2)
		return (NULL);
	p = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_memmove(p, s1, len1);
	ft_memmove(p + len1, s2, len2);
	return (p);
}
