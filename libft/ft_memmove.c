/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:29:04 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/29 22:02:50 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dst;
	s = (const unsigned char *)src;
	if (!dst && !src)
		return (NULL);
	if (d > s && d < s + len)
	{
		d += len -1;
		s += len -1;
		while (len--)
			*(d--) = *(s--);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
// CP
// memcpy の上位互換
// indexを見る