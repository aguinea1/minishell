/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_match_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/23 21:18:34 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell_bonus.h"
#include "../../inc/minishell.h"

int	check_final_segment(const char *pattern, const char *filename, int n)
{
	int			pat_tail_len;
	const char	*p_tail;
	size_t		len;

	pat_tail_len = 0;
	p_tail = pattern + n;
	len = ft_strlen(pattern);
	if (len == 0 || pattern[len - 1] == '*')
		return (0);
	if (len > 0 && pattern[n - 1] != '*')
	{
		while (p_tail > pattern && *(p_tail - 1) != '*')
		{
			p_tail--;
			pat_tail_len++;
		}
		if (ft_strlen(filename) < (size_t)pat_tail_len
			|| ft_strncmp(filename + ft_strlen(filename) - pat_tail_len, p_tail,
				pat_tail_len) != 0)
			return (1);
	}
	return (0);
}

int	check_initial_segment(const char *p, const char *filename, int *seg_len)
{
	if (*p != '*')
	{
		while (p[*seg_len] && p[*seg_len] != '*')
			*seg_len += 1;
		if (ft_strncmp(filename, p, *seg_len) != 0)
			return (1);
	}
	return (0);
}

int	process_segment(const char **pos, const char **p, int seg_len, int n)
{
	int	found;

	found = 0;
	while (**pos && ((*p - *pos) < n))
	{
		if (ft_strncmp(*pos, *p, seg_len) == 0)
		{
			found = 1;
			break ;
		}
		(*pos)++;
	}
	return (found);
}

int	handle_pattern_segments(const char *pattern, const char *filename, int n)
{
	const char	*p;
	const char	*pos;
	int			seg_len;

	p = pattern;
	pos = filename;
	while ((p - pattern) < n && *p)
	{
		while ((p - pattern) < n && *p == '*')
			p++;
		seg_len = 0;
		while ((p - pattern) + seg_len < n && p[seg_len] && p[seg_len] != '*')
			seg_len++;
		if (seg_len == 0)
			break ;
		if (!process_segment(&pos, &p, seg_len, n))
			return (1);
		p += seg_len;
		pos += seg_len;
	}
	if (check_final_segment(pattern, filename, n))
		return (1);
	return (0);
}
