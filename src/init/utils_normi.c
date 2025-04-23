/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_normi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:57:00 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/23 21:28:27 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>

int	collect_directory_files(DIR *dir, char ***files)
{
	struct dirent	*entry;
	int				count;

	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.')
		{
			*files = ft_realloc(*files, count * sizeof(char *),
					(count + 1) * sizeof(char *));
			if (!*files)
				return (-1);
			(*files)[count++] = ft_strdup(entry->d_name);
		}
		entry = readdir(dir);
	}
	return (count);
}

static int	normi_wow(const char *s, int j)
{
	if (j > 1)
	{
		if (s[j - 1] != ' ')
		{
			while (s[j] != ' ' && j > 0)
				j--;
			if (j == 0)
				return (0);
		}
	}
	return (1);
}

char	*ft_strchr_wildcard(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\'')
			while (s[i++] != '\'')
				;
		if (s[i] == '"')
			while (s[i++] != '"')
				;
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	if (normi_wow(s, i))
		return ((char *)&s[i]);
	return (NULL);
}
