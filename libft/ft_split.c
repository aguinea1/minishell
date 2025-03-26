/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:46:47 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/30 12:54:48 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	safe_malloc(char **token_v, int position, size_t buffer)
{
	int	i;

	i = 0;
	token_v[position] = malloc(buffer);
	if (!token_v[position])
	{
		while (i < position)
			free(token_v[i++]);
		free(token_v);
		return (1);
	}
	return (0);
}

static int	fill(char **token_v, char const *s, char delimiter)
{
	size_t	len;
	int		position;

	position = 0;
	while (*s)
	{
		len = 0;
		while (*s == delimiter && *s)
			s++;
		len = 0;
		while (*s != delimiter && *s)
		{
			len++;
			s++;
		}
		if (len)
		{
			if (safe_malloc(token_v, position, len + 1))
				return (1);
		}
		ft_strlcpy(token_v[position], s - len, len + 1);
		position++;
	}
	return (0);
}

static size_t	count_tokens(char const *s, char delimiter)
{
	size_t	tokens;
	int		new_token;

	tokens = 0;
	while (*s)
	{
		while (*s == delimiter && *s)
			s++;
		new_token = 0;
		while (*s != delimiter && *s)
		{
			if (new_token == 0)
			{
				tokens++;
				new_token = 1;
			}
			s++;
		}
	}
	return (tokens);
}

char	**ft_split(char const *s, char c)
{
	size_t	tokens;
	char	**token_v;

	if (s == NULL)
		return (NULL);
	tokens = 0;
	tokens = count_tokens(s, c);
	token_v = malloc((tokens + 1) * sizeof(char *));
	if (!token_v)
		return (NULL);
	token_v[tokens] = NULL;
	if (fill (token_v, s, c))
		return (NULL);
	return (token_v);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*s = "   Hello there  !!!  ";
	char	**v = ft_split(s, ' ');

	while (*v)
	{
		printf("%s\n", *v++);
	}
	return (0);
}*/
