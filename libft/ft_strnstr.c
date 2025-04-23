/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 19:42:52 by tishihar          #+#    #+#             */
/*   Updated: 2024/05/20 23:14:12 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!needle_len)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (*haystack && needle_len <= len)
	{
		if (!ft_strncmp(needle, haystack, needle_len))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
