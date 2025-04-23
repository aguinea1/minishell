/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/23 21:29:51 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>
#include <stdbool.h>

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

char	**get_dir_elements(void)
{
	DIR		*dir;
	char	**files;
	int		count;

	files = NULL;
	dir = opendir(".");
	if (!dir)
		return (perror("opendir"), NULL);
	count = collect_directory_files(dir, &files);
	closedir(dir);
	if (count == -1)
		return (ft_free_array(files), NULL);
	files = ft_realloc(files, count * sizeof(char *),
			(count + 1) * sizeof(char *));
	files[count] = NULL;
	return (files);
}

static char	*process_single_wildcard(char *input, int *pos)
{
	int		j;
	char	*pattern;
	char	*expanded;
	char	*new_input;

	j = *pos;
	while (j > 0 && input[j - 1] != ' ')
		j--;
	while (input[*pos] && input[*pos] != ' ')
		(*pos)++;
	pattern = ft_strndup(&input[j], *pos - j);
	expanded = expand_wildcard(j, *pos, pattern);
	free(pattern);
	if (expanded)
	{
		new_input = manage_new_input(input, j, pos, expanded);
		return (new_input);
	}
	return (input);
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
			while (new_input[++i] != '\'')
				;
		if (new_input[i] == '"')
			while (new_input[++i] != '"')
				;
		if (new_input[i] == '*')
			new_input = process_single_wildcard(new_input, &i);
		else if (new_input[i])
			i++;
	}
	return (new_input);
}
