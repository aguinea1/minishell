/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*char	ft(unsigned int i, char s)
{
	if (s >= 'A' && s <= 'Z')
		s += 32;
	return (s);
}*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = malloc(ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	if (!f)
	{
		ft_strlcpy(str, s, ft_strlen(s) + 1);
		return (str);
	}
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str [i] = '\0';
	return (str);
}
/*
#include <stdio.h>

int	main(void)
{
	char	s[] = "JHJH";

	printf("%s\n", ft_strmapi(s, ft));
	return (0);
}*/
