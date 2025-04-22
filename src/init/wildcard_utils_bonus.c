/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/22 12:46:04 by aguinea          ###   ########.fr       */
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

static size_t	calculate_total_length(char **files,
				char *pattern, int pattern_len)
{
	size_t	total_len;
	int		i;

	total_len = 0;
	i = 0;
	while (files && files[i])
	{
		if (ft_strncmp_wildcard(files[i], pattern, pattern_len) == 0)
			total_len += ft_strlen(files[i]) + 1;
		i++;
	}
	return (total_len);
}

char	*expand_wildcard(int start, int end, char *pattern)
{
	char	**files;
	char	*result;
	size_t	total_len;
	int		pattern_len;

	files = get_dir_elements();
	if (!files)
		return (NULL);
	pattern_len = end - start;
	total_len = calculate_total_length(files, pattern, pattern_len);
	if (total_len == 0)
		return (ft_free_array(files), NULL);
	result = malloc(total_len + 1);
	if (!result)
		return (ft_free_array(files), NULL);
	result[0] = '\0';
	append_matches_to_result(result, files, pattern, pattern_len);
	ft_free_array(files);
	return (result);
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

char	*handle_wildcard_at(char *input, int *i)
{
	int		start;
	int		end;
	char	*pattern;
	char	*expanded;

	start = *i;
	while (start > 0 && input[start - 1] != ' ')
		start--;
	end = *i;
	while (input[end] && input[end] != ' ')
		end++;
	pattern = ft_strndup(&input[start], end - start);
	if (!pattern)
		return (NULL);
	expanded = expand_wildcard(start, end, pattern);
	free(pattern);
	if (expanded)
		return (manage_new_input(input, start, i, expanded));
	return (input);
}
