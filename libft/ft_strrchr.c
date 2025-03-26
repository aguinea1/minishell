/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:53:54 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/19 16:42:28 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (c == 0)
		return ((char *)&s[i]);
	while (i >= 0)
	{
		if (s[i] == (char) c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	s[] = "Hola";
	char	*result;

	result = ft_strrchr(s, '\0');
	if (result != NULL)
		printf("%s\n", result);
	else
		printf("NULL");
	return (0);
}*/
