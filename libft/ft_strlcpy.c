/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:11:18 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/26 17:55:47 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	size;

	len = ft_strlen(src);
	if (dstsize)
	{
		size = dstsize - 1;
		while (*src && size--)
			*(dst++) = *(src++);
		*dst = '\0';
	}
	return (len);
}

// CP
/*
#include <string.h>
int main (){
	char dst6[] ="!!!woooooorld!!";
	printf("%s: Before\n", dst6);
	ft_strlcpy(dst6, "hello !", 2);
	printf("%s: After ft\n", dst6);
	strlcpy(dst6, "hello !", 2);
	printf("%s: After std\n", dst6);


	char dst1[] = "abcde";
	printf("%s : dst\n", dst1);
	ft_strlcpy(dst1, "99999", 5);
	printf("%s : after\n", dst1);

	char dst2[] = "abcde";
	printf("%s : dst/std\n", dst2);
	strlcpy(dst2, "99999", -1);
	printf("%s : after\n", dst2);

}
//*/

// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	i;
// 	size_t	len;

// 	i = 0;
// 	len = ft_strlen(src);
// 	if (dstsize)
// 	{
// 		while (src[i] && i < dstsize - 1)
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	return (len);
// }