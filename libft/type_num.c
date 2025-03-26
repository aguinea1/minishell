/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:27:24 by arcebria          #+#    #+#             */
/*   Updated: 2024/10/10 17:40:04 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int *count)
{
	unsigned int	nbr;

	if (n < 0)
	{
		ft_putchar('-', count);
		nbr = -n;
	}
	else
		nbr = n;
	if (nbr >= 10)
		ft_putnbr(nbr / 10, count);
	ft_putchar((nbr % 10) + '0', count);
}

void	ft_putuns(unsigned int n, int *count)
{
	if (n >= 10)
		ft_putuns(n / 10, count);
	ft_putchar((n % 10) + '0', count);
}
