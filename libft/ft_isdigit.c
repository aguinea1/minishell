/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 12:27:13 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/17 19:15:41 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
#include<stdio.h>
int	main(void)
{
	int	c;
	int	a;

	c = 58;
	a = 57;
	printf("%d, %d\n", ft_isdigit(c), ft_isdigit(a));
	return (0);
}*/
