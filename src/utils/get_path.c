/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tishihar <tishihar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:02:52 by tishihar          #+#    #+#             */
/*   Updated: 2025/04/28 17:52:40 by tishihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*find_value(char *str, int shift);
static	char	*join_path(char *dir, char *name);
static	char	*validate_and_get_path(char **paths, char *name);

// serch key in envp_array, and get value.
char	*get_env_value_bykey(char **envp, char *key)
{
	int	len;

	len = ft_strlen(key);
	while (*envp)
	{
		if (ft_strncmp(*envp, key, len) == 0 && *(*envp + len) == '=')
			return (find_value(*envp, len + 1));
		envp++;
	}
	return (NULL);
}

// we give "name" to this get_path(), and we get FULL_PATH.
// ex ) "ls" -> "/usr/bin/ls" , "/usr/bin/ls" -> "/usr/bin/ls"
char	*get_cmd_path(char **envp, char	*name)
{
	char	**path;
	char	*result;

	if (!*name || !name)
		return (NULL);
	if (*name == '/' || *name == '.')
		return (ft_strdup(name));
	path = ft_split(get_env_value_bykey(envp, "PATH"), ':');
	if (!path)
		return (NULL);
	result = validate_and_get_path(path, name);
	if (!result)
	{
		destroy_split(path);
		return (NULL);
	}
	destroy_split(path);
	return (result);
}

static	char	*find_value(char *str, int shift)
{
	return (str + shift);
}

static	char	*join_path(char *dir, char *name)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, name);
	free(temp);
	return (result);
}

// validate, and output PATH we can access.
static	char	*validate_and_get_path(char **paths, char *name)
{
	char	*curr_path;

	curr_path = NULL;
	while (*paths)
	{
		curr_path = join_path(*paths, name);
		if (!curr_path)
			return (NULL);
		if (access(curr_path, X_OK) == 0)
			return (curr_path);
		free(curr_path);
		paths++;
	}
	return (NULL);
}
