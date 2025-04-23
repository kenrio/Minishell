/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:34:29 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/30 23:10:56 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	n;

	if (!s)
		return (NULL);
	n = ft_strlen(s);
	if (start)
	{
		if (n > start)
			n = start;
		return (ft_substr(s + n, 0, len));
	}
	if (n > len)
		n = len;
	p = ft_calloc(n + 1, sizeof(char));
	if (p == NULL)
		return (NULL);
	ft_memmove(p, s, n);
	return (p);
}
// CP
// nを３０までに決める
	// p = malloc(n + 1);
	// if (p == NULL)
	// 	return (NULL);
	// memmove(p, s, n);
	// p[n] = '\0';
	// return (p);