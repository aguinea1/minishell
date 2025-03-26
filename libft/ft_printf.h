/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:16:01 by arcebria          #+#    #+#             */
/*   Updated: 2024/10/10 18:16:08 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(char const *str, ...);
void	ft_putchar(int c, int *count);
void	ft_putstr(char *s, int *count);
void	ft_putnbr(int n, int *count);
void	ft_putuns(unsigned int n, int *count);
void	ft_puthex(unsigned int n, const char f, int *count);
void	ft_putptr(unsigned long n, int *count);
void	ft_putp(unsigned long n, int *count);

#endif
