/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:58:02 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/30 16:41:52 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if ((dest == NULL && src == NULL))
		return (NULL);
	i = 0;
	while (i < n)
	{
		*((char *)dest + i) = *((const char *) src + i);
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	char	dest[] = "";
	char	src[] = "";

	ft_memcpy(dest, src, 5);
	printf("%s\n", dest);
	return (0);
}*/
