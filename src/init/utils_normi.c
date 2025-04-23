/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_normi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:57:00 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/23 16:41:36 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/minishell_bonus.h"
#include <dirent.h>
#include <stdlib.h>

void	skip_quoted_sections(char *input, char *new_input, int *i)
{
	if (new_input[*i] == '\'')
		while (input[++(*i)] != '\'')
			;
	if (new_input[*i] == '"')
		while (input[++(*i)] != '"')
			;
}

char	*handle_wildcard(char *new_input, int *i)
{
	int		j;
	char	*pattern;
	char	*expanded;

	j = *i;
	while (j > 0 && new_input[j - 1] != ' ')
		j--;
	while (new_input[*i] && new_input[*i] != ' ')
		(*i)++;
	pattern = ft_strndup(&new_input[j], *i - j);
	expanded = expand_wildcard(j, *i, pattern);
	free(pattern);
	return (expanded);
}
