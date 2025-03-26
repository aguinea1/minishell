/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:32:36 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/27 14:29:30 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
void	ft(unsigned int i, char *s)
{
	if (i == 0)
	{
		if (*s >= 'a' && *s <= 'z')
			*s -= 32;
	}
}*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	if (!*s || !f)
		return ;
	while (s[i])
	{
		(*f)(i, &s[i]);
		i++;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char	s[] = "hola";

	ft_striteri(s, ft);
	printf("%s\n", s);
	return (0);
}*/
