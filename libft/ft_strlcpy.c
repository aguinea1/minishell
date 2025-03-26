/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:34:33 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/30 15:40:23 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (dst == NULL || src == NULL || !size)
		return (len);
	while (*src && --size)
		*dst++ = *src++;
	*dst = '\0';
	return (len);
}
/*
#include <stdio.h>
int	main(void)
{
	char	src[] = "lorem ipsum dolor sit amet";
	char	dst[10];

	printf("%ld\n", ft_strlcpy(dst, src, 15));
	printf("%s\n", dst);
	return (0);
}*/
