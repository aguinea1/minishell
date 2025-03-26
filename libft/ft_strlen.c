/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:06:38 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/17 19:14:55 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
/*
size_t	ft_strlen(const char *str)
{
	const char *s;

	s = str;
	while (*s)
		s++;
	return (s - str);
}
#include<stdio.h>
int	main(void)
{
	char	str[] = "dkhgis";

	printf("%ld\n", ft_strlen(str));
	return (0);
}*/
