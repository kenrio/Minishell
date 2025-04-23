/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 22:25:56 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/31 13:40:49 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		len_src;
	size_t		len_dst;

	if (!dst && dstsize == 0)
		return (0);
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (len_dst >= dstsize)
		return (len_src + dstsize);
	else
		ft_strlcpy(dst + len_dst, src, dstsize - len_dst);
	return (len_dst + len_src);
}

// CP

// size_t ft_strlcat(char *dst, const char *src, size_t dstsize) {
//     size_t dst_len = ft_strlen(dst);
//     size_t src_len = ft_strlen(src);
//     size_t to_copy = dstsize - dst_len;

//     if (dst_len < dstsize - 1) {
//         ft_strlcpy(dst + dst_len, src, to_copy);
//     }

//     return dst_len + src_len; // 元々の dst の長さと src の長さの合計
// }
//("123456789", "AAAAA", 2)

/*
// concat
// return 総バッファ数 
#include <string.h>
int main(){
	// char dst1[20] ="AAAAAAAAAA\0";
	// char dst2[20] ="AAAAAAAAAA\0";
	// const char*src = "12345678";
	// size_t dstsize = 12;
	// printf("dst: %s(%lu), src: %s(%lu), dstsize: %lu\n", dst1, 
	   strlen(dst1), src, strlen(src), dstsize);
	// size_t result1=strlcat(dst1, src,dstsize);
	// size_t result2=ft_strlcat(dst2, src,dstsize);
	// printf("strlcat   : result=%lu, dst=\"%s\"\n", result1, dst1);
	// printf("strlcat   : result=%lu, dst=\"%s\"\n", result1, dst1);
	// printf("ft_strlcat: result=%lu, dst=\"%s\"\n", result2, dst2);


	// char dst10[60] = "there is no stars in the sky";
	// char src10[60] = "the cake is a lie !\0I'm hidden lol\r\n";;
	// size_t size10 = strlen(dst10) + strlen(src10);
	// printf("dst:%s(%lu), src:%s(%lu), return(%lu)",dst10,strlen(dst10),
	//     src10,strlen(src10),ft_strlcat(dst10,src10,size10));
	char dst10[60] = "CCCCCAAAAAAAAA";
	if (len_dst < dstsize)
	{
		dst += len_dst;
		dst_end = dst + ((dstsize - len_dst) - 1);
		while (*src && (dst < dst_end))
			*(dst++) = *(src++);
		*dst = '\0';
	}
	else
		return (len_src + dstsize);
	return (len_dst + len_src);
	
}
///*/