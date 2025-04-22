/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/22 13:34:31 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>

void	ft_free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*manage_new_input(char *new_input, int j, int *i, char *expanded)
{
	char	*old_input;
	char	*result;

	old_input = new_input;
	result = fuse_results(old_input, j, i, expanded);
	free(old_input);
	free(expanded);
	return (result);
}

int	add_file(char ***files, int *count, const char *filename)
{
	char **new_files;

    new_files = ft_realloc(*files, (*count) * sizeof(char *),
                           (*count + 1) * sizeof(char *));
    if (!new_files)
        return (0);
    new_files[*count] = ft_strdup(filename);
    if (!new_files[*count])
        return (ft_free_array(new_files), 0);
    (*count)++;
    *files = new_files;
    return (1);
}

char	**get_dir_elements(void)
{
	DIR		*dir;
	char	**files;

	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	files = read_and_filter_dir(dir);
	return (files);
}

char	*manage_wildcard(char *input)
{
	int		i;
	char	*new_input;

	i = 0;
	new_input = ft_strdup(input);
	while (new_input[i])
	{
		if (new_input[i] == '\'')
			while (new_input[++i] && new_input[i] != '\'')
				;
		else if (new_input[i] == '"')
			while (new_input[++i] && new_input[i] != '"')
				;
		else if (new_input[i] == '*')
		{
			new_input = handle_wildcard_at(new_input, &i);
			if (!new_input)
				return (NULL);
		}
		else
			i++;
	}
	return (new_input);
}
