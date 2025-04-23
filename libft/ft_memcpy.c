/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 05:33:39 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/19 16:02:33 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;

	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	if (!dst && !src)
		return (NULL);
	while (n--)
		*(d++) = *(s++);
	return (dst);
}

/*
// memcpyはmemmoveの下位互換
#include <stdio.h>
#include <string.h>
int main(void)
{
	// print test
	const char *dst1 = "helllllo!!!woooooorld!!";
	char _dst1[] = "helllllo!!!woooooorld!!";
	int tmp;
	printf("%s: this is a origin\n", dst1);
	printf("%p: pointer\n", dst1);
	printf("%p: array\n", _dst1);
	printf("%p: int ptr\n", &tmp);
	fflush(stdout);



	//dst < src
	char dst2[] ="helllllo!!!woooooorld!!";
	ft_memcpy(dst2, dst2+3, 10);
	printf("%s: this is a dst2\n", dst2);
	
	//dst > src
	char dst3[] ="helllllo!!!woooooorld!!";
	ft_memcpy(dst3+3, dst3, 10);
	printf("%s: this is a dst3: mine_memcpy\n", dst3);

	//dst > src
	// char dst4[] ="helllllo!!!woooooorld!!";
	// memcpy(dst4+3, dst4, 10);
	// printf("%s: this is a dst4: origin_memcpy\n", dst4);

	//memmove

	//dst > src
	char dst5[] ="helllllo!!!woooooorld!!";
	memmove(dst5+3, dst5, 10);
	printf("%s: this is a dst5: memmove\n", dst5);

	char dst6[] ="!!!woooooorld!!";
	memmove(dst6, "hello !", 1);
	printf("%s: this is a dst5: memmove\n", dst5);

	return (0);
}
//*/