/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/23 21:39:43 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell_bonus.h"
#include "../../inc/minishell.h"

int	ft_strncmp_wildcard(const char *filename, const char *pattern,
		int n)
{
	int	initial_check;
	int	seg_len;

	seg_len = 0;
	initial_check = check_initial_segment(pattern, filename, &seg_len);
	if (initial_check)
		return (1);
	return (handle_pattern_segments(pattern + seg_len, filename + seg_len, n));
}

static char	*build_expanded_result(char **files, char *pattern,
			int pattern_len, size_t total_len)
{
	char	*result;
	int		i;

	result = malloc(total_len + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (files && files[i])
	{
		if (ft_strncmp_wildcard(files[i], pattern, pattern_len) == 0)
		{
			ft_strcat(result, files[i]);
			ft_strcat(result, " ");
		}
		i++;
	}
	return (result);
}

char	*expand_wildcard(int start, int end, char *pattern)
{
	char	**files;
	char	*result;
	size_t	total_len;
	int		pattern_len;
	int		i;

	files = get_dir_elements();
	if (!files)
		return (ft_free_array(files), NULL);
	result = NULL;
	total_len = 0;
	pattern_len = end - start;
	i = -1;
	while (files && files[++i])
	{
		if (ft_strncmp_wildcard(files[i], pattern, pattern_len) == 0)
			total_len += ft_strlen(files[i]) + 1;
	}
	if (total_len == 0)
		return (ft_free_array(files), NULL);
	result = build_expanded_result(files, pattern, pattern_len, total_len);
	if (!result)
		return (ft_free_array(files), NULL);
	return (ft_free_array(files), result);
}

char	*fuse_results(char *new_input, int start, int *end, char *expanded)
{
	char	*before;
	char	*after;
	char	*tmp;
	char	*result;
	int		expanded_len;

	before = ft_strndup(new_input, start);
	after = ft_strdup(new_input + *end);
	tmp = ft_strjoin(before, expanded);
	if (!tmp)
		return (free(before), free(after), NULL);
	free(before);
	result = ft_strjoin(tmp, after);
	if (!result)
		return (free(after), NULL);
	free(tmp);
	free(after);
	expanded_len = ft_strlen(expanded);
	*end = start + expanded_len;
	return (result);
}
