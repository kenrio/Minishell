/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:22:38 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/24 17:32:08 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = (unsigned char *)b;
	while (len--)
		*(p++) = (unsigned char)c;
	return (b);
}

/*
// memory set
int main(void)
{
	char str[50] = "Hello, world! This is a test string.";
	int c= '*';
	size_t len = 10;

	printf("Original string is : %s \n", str);
	ft_memset(str+3, c, len);
	printf("MOdified str is: %s \n",str);

	return 0;
}
*/