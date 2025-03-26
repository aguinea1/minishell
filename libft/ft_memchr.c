/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:25:39 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/30 17:00:30 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return (&ptr[i]);
		i++;
	}
	return (NULL);
}

/*#include <stdio.h>
int	main(void)
{
	char	tab[] = "hola";
	int	c;
	void	*result;

	c = 'p';
	result = ft_memchr(tab, c, 8);
	if (result != NULL)
		printf("%c\n", *((char *)result));
	else
		printf("NULL");
	return (0);
}*/
