/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:44:18 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/23 19:19:21 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int	size_s1;

	if (!s1 || !set)
		return (0);
	while (ft_strchr(set, *s1) && *s1)
		s1++;
	size_s1 = ft_strlen((char *)s1);
	while (ft_strchr(set, s1[size_s1]) && size_s1 > 0)
		size_s1--;
	return (ft_substr((char *)s1, 0, size_s1 + 1));
}
/*
//primer while
//es posa el set primer per a que avance internament en la funcio strchr
//ens interesa que avance *s1 dins de la funcio
//segon while
//no s'utilitza strrchr perque es donaria la volta a s1
//i compararia el principi de s1 amb set
//es vol comparar set amb el final de s1

#include <stdio.h>

int	main(void)
{
	char	s1[] = "ttttssseesteHolasstetstestetststes";
	char	set[] = "set";

	printf("%s", ft_strtrim(s1, set));
	return (0);
}*/
