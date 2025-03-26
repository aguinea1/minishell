/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:20:49 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/01 21:15:19 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strspn(const char *s, const char *accept)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (accept[j] && s[i] != accept[j])
			j++;
		if (accept[j] == '\0')
			return (i);
		i++;
	}
	return (i);
}
