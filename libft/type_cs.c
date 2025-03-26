/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_cs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:39:03 by arcebria          #+#    #+#             */
/*   Updated: 2024/10/11 15:53:31 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar(int c, int *count)
{
	if (write(1, &c, 1) != 1)
	{
		*count = -1;
		return ;
	}
	(*count)++;
}

void	ft_putstr(char *s, int *count)
{
	int	i;

	i = 0;
	if (s == 0)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (s[i])
	{
		ft_putchar(s[i], count);
		i++;
	}
}
