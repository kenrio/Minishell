/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 06:42:14 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/20 23:10:36 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	find;

	find = (char)c;
	while (*s)
	{
		if (*s == find)
			return ((char *)s);
		s++;
	}
	if (find == '\0')
		return ((char *)s);
	return (NULL);
}

/*
#include <string.h>
int main()
{
	char *str = "hello";
	printf("%s: result of mine\n", ft_strchr(str, 'a'));
	printf("%s: result of std", strchr(str, 'a'));

}
*/