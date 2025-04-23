/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 19:22:28 by tishihar          #+#    #+#             */
/*   Updated: 2025/01/08 16:16:07 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && count > SIZE_MAX / size)
		return (NULL);
	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, count * size);
	return (p);
}

// int	main(void)
// {
// 	printf("%p : %p : %p", ft_calloc(0, 0), calloc(0, 0), NULL);
// 	return (0);
// }

/*
void	pf(void)
{
	int	a;

	printf("%d\n",a);
	printf("%p\n",&a);
}
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	void	*p;

	printf("sizeof void pointer %lu\n",sizeof(void *));
	printf("malloc(0) return (non-NULL pointer %p\n", &p));
	printf("malloc(0) return (non-NULL pointer %p\n", p));
	p = malloc(0);
	printf("malloc(0) return (non-NULL pointer %p\n", &p));
	printf("malloc(0) return (non-NULL pointer %p\n", p));
	((char *)p)[0] = 0;
	//((char *)p)[100] = 0;
	//fflush(stdout);//
	// int a;
	// printf("number  %d\n",a-1);
	// printf("address %p\n",&a);
	// pf();
	// //fflush(stdout);
	// printf("%p\n",main);
	if (p == NULL)
		printf("malloc(0) do not work.\n");
	else
		printf("malloc(0) return (non-NULL pointer %p", p));
	return (0);
}
*/