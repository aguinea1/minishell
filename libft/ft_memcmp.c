/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:32:46 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/30 17:12:39 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr1;
	const unsigned char	*ptr2;

	i = 0;
	ptr1 = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	if (!n)
		return (0);
	while (i < n - 1 && ptr1[i] == ptr2[i])
		i++;
	return (ptr1[i] - ptr2[i]);
}

/*#include <stdio.h>
int	main(void)
{
	char	s1[] = "aaaaa";
	char	s2[] = "aaa";

	printf("%d\n", ft_memcmp(s1, s2, 20));
	return (0);
}*/
