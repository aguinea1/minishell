/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_xXp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:54:29 by arcebria          #+#    #+#             */
/*   Updated: 2024/10/10 18:01:34 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex(unsigned int n, const char f, int *count)
{
	char	*base;

	if (f == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n >= 16)
	{
		ft_puthex((n / 16), f, count);
		ft_puthex((n % 16), f, count);
	}
	else
		ft_putchar(base[n], count);
}

void	ft_putp(unsigned long n, int *count)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		ft_putp(n / 16, count);
	ft_putchar(base[n % 16], count);
}

void	ft_putptr(unsigned long n, int *count)
{
	if (n == '\0')
		ft_putstr("(nil)", count);
	else
	{
		ft_putstr("0x", count);
		ft_putp(n, count);
	}
}
