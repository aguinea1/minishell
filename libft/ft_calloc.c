/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:17:00 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/21 17:01:05 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*buffer;

	buffer = (void *)malloc(nmemb * size);
	if (!buffer)
		return (NULL);
	ft_bzero(buffer, nmemb * size);
	return (buffer);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s", (char *)ft_calloc('0', '0'));
	return (0);
}*/
