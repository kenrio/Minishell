/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 00:27:28 by tishihar          #+#    #+#             */
/*   Updated: 2024/06/01 00:49:14 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countdigit_helper(long n, size_t count)
{
	if (n == 0 && count == 0)
		return (1);
	else if (n == 0)
		return (count);
	return (ft_countdigit_helper(n / 10, count + 1));
}

static size_t	ft_countdigit(long n)
{
	return (ft_countdigit_helper(n, 0));
}

// 登録するポインタを返す。
static char	*ft_setitoa(long n, char *p)
{
	char	*curr;

	if (n < 10)
	{
		*p = n + '0';
		return (p + 1);
	}
	curr = ft_setitoa(n / 10, p);
	*curr = (n % 10) + '0';
	return (curr + 1);
}

char	*ft_itoa(int n)
{
	char	*p;
	size_t	len;
	long	number;
	char	*temp;

	number = (long)n;
	len = ft_countdigit(number) + (number < 0);
	p = ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (NULL);
	temp = p;
	if (number < 0)
	{
		*(p++) = '-';
		number *= -1;
	}
	ft_setitoa(number, p);
	return (temp);
}
