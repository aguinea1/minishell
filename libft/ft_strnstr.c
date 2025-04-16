/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	j = 0;
	if (!*little)
		return ((char *)big);
	while (big[j] && j < len)
	{
		i = 0;
		while ((j + i) < len && little[i] == big[j + i] && little[i])
		{
			i++;
			if (little[i] == '\0')
				return ((char *)&big[j]);
		}
		j++;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main()
{
	char	l[] = "la";
	char	b[] = "holla";
	char	*result;

	result = ft_strnstr(b, l, 3);
	printf("%s", (char *)result);
	return (0);
}*/
