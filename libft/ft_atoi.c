/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:11:12 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/30 13:13:25 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ispace(int c)
{
	if (c == 32 || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	while (ispace(*nptr) == 1)
		nptr++;
	sign = 1;
	if (*nptr == '+')
		nptr++;
	else if (*nptr == '-')
	{
		sign *= -1;
		nptr++;
	}
	result = 0;
	while (ft_isdigit(*nptr) == 1)
	{
		result = (result * 10) + (*nptr - '0');
		nptr++;
	}
	result *= sign;
	return (result);
}
/*
#include <stdio.h>

int	main(void)
{
	char	tab[] = "-798";

	printf("%d\n", ft_atoi(tab));
	return (0);
}*/
