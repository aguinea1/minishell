/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 09:19:05 by arcebria          #+#    #+#             */
/*   Updated: 2024/09/23 09:56:35 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
/*
#include <stdio.h>

int	main(void)
{
	char tab[5] = "aaaaa";

	ft_bzero(tab, 5);
	printf("%s\n", tab);
	return (0);
}*/
