/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:55:35 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/31 23:06:03 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_sp_countwords(char *str, char f)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && *str == f)
			str++;
		if (*str && *str != f)
		{
			count++;
			while (*str && *str != f)
				str++;
		}
	}
	return (count);
}

static size_t	ft_sp_strlen(char *str, char c)
{
	size_t	len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static void	ft_sp_clean(char **origin, char **curr)
{
	while (origin <= --curr)
		free (*curr);
	free (origin);
}

static int	ft_sp_add(char **result, char **start, char *str, char c)
{
	size_t	len;

	while (*str)
	{
		while (*str && *str == c)
			str++;
		len = ft_sp_strlen(str, c);
		if (len > 0)
		{
			*result = ft_substr(str, 0, len);
			if (!(*result))
			{
				ft_sp_clean(start, result);
				return (0);
			}
			result++;
		}
		str += len;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	**output_temp;
	char	*str;

	if (!s)
		return (NULL);
	str = (char *)s;
	result = ft_calloc(ft_sp_countwords(str, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	output_temp = result;
	if (ft_sp_add(result, output_temp, str, c) == 0)
		return (NULL);
	return (output_temp);
}
