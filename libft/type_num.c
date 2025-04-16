/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:10:03 by aguinea          ###   ########.fr       */
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
