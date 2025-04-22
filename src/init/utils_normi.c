/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_normi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:57:00 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/22 12:42:39 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>

void	append_matches_to_result(char *result, char **files,
			char *pattern, int pattern_len)
{
	int	i;

	i = 0;
	while (files[i])
	{
		if (ft_strncmp_wildcard(files[i], pattern, pattern_len) == 0)
		{
			ft_strcat(result, files[i]);
			ft_strcat(result, " ");
		}
		i++;
	}
}

char	**read_and_filter_dir(DIR *dir)
{
	struct dirent	*entry;
	char			**files;
	int				count;

	files = NULL;
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		entry = readdir(dir);
		if (entry->d_name[0] != '.')
		{
			if (!add_file(&files, &count, entry->d_name))
				return (ft_free_array(files), NULL);
		}
	}
	files = ft_realloc(files, count * sizeof(char *),
			(count + 1) * sizeof(char *));
	if (files)
		files[count] = NULL;
	return (files);
}
