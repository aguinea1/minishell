/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
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
