/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrmchr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <wingstonetone9.8@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 19:28:16 by tishihar          #+#    #+#             */
/*   Updated: 2025/03/18 20:01:46 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_chars_in_set(char *str, char *set);

//  strrmchr（） can remove char in set string.
char	*strrmchr(char *str, char *set)
{
	int		count;
	char	*result;
	char	*temp;

	if (!str || !set)
        return (NULL);
	count = count_chars_in_set(str, set);
	result = ft_calloc(ft_strlen(str) - count + 1, sizeof(char));
	if (!result)
		return (NULL);
	temp = result;
	while (*str)
	{
		if (!ft_strchr(set, *str))
		{
			*temp = *str;
			temp++;
		}
		str++;
	}
	return (result);
}

static int count_chars_in_set(char *str, char *set)
{
	int		count;

	count = 0;
	while (*str)
	{
		if (ft_strchr(set, *str))
			count++;
		str++;
	}
	return (count);
}
