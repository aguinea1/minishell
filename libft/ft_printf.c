/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:05:13 by arcebria          #+#    #+#             */
/*   Updated: 2024/10/10 18:15:02 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	format_analizer(char f, va_list args, int *count)
{
	if (f == 's')
		ft_putstr(va_arg(args, char *), count);
	else if (f == 'c')
		ft_putchar(va_arg(args, int), count);
	else if (f == 'd' || f == 'i')
		ft_putnbr(va_arg(args, int), count);
	else if (f == 'u')
		ft_putuns(va_arg(args, unsigned int), count);
	else if (f == 'x' || f == 'X')
		ft_puthex(va_arg(args, unsigned int), f, count);
	else if (f == 'p')
		ft_putptr(va_arg(args, unsigned long int), count);
	else if (f == '%')
		ft_putchar('%', count);
	else
		return (-1);
	return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i] == '\0')
				return (-1);
			else if (format_analizer(str[i], args, &count) == -1)
				return (-1);
		}
		else
			ft_putchar(str[i], &count);
		i++;
	}
	va_end(args);
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s----------------------------\n%s", RED, END);
	printf("%sTESTING ---> %%c \n%s", GREEN, END);
	printf("Function printf = %c \n", '\\');
	int result = ft_printf("My function = %c \n", '\\');
	printf("Total data = %i \n", result);
	ft_printf("Total data = %i \n", result);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING ---> %%s \n%s", GREEN, END);
	char str[] = "hola";
	printf("Function printf = %s \n", str);
	int result2 = ft_printf("My function = %s \n", str);
	printf("Total data = %i \n", result2);
	ft_printf("Total data = %i \n", result2);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING ---> %%d \n%s", GREEN, END);
	printf("Function printf = %d, %d, %d \n", -0, 42, -42);
	int result3 = ft_printf("My function = %d, %d, %d \n", -0, 42, -42);
	printf("Total data = %i \n", result3);
	ft_printf("Total data = %i \n", result3);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING ---> %%i \n%s", GREEN, END);
	printf("Function printf = %i \n", 2024);
	int result4 = ft_printf("My function = %i \n", 2024);
	printf("Total data = %i \n", result4);
	ft_printf("Total data = %i \n", result4);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING NEG NUM ---> %%u \n%s", GREEN, END);
	printf("Function printf = %u \n", -2);
	int results = ft_printf("My function = %u \n", -2);
	printf("Total data = %i \n", results);
	ft_printf("Total data = %i \n", results);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING ---> %%u \n%s", GREEN, END);
	printf("Function printf = %u \n", 42);
	int resultss = ft_printf("My function = %u \n", 42);
	printf("Total data = %i \n", resultss);
	ft_printf("Total data = %i \n", resultss);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING ---> %%x \n%s", GREEN, END);
	printf("Function printf = %x \n", 42);
	int result5 = ft_printf("My function = %x \n", 42);
	printf("Total data = %i \n", result5);
	ft_printf("Total data = %i \n", result5);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING NEG NUM ---> %%x \n%s", GREEN, END);
	printf("Function printf = %x \n", -42);
	int resultx = ft_printf("My function = %x \n", -42);
	printf("Total data = %i \n", resultx);
	ft_printf("Total data = %i \n", resultx);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING ---> %%X \n%s", GREEN, END);
	printf("Function printf = %X \n", 2024);
	int result6 = ft_printf("My function = %X \n", 2024);
	printf("Total data = %i \n", result6);
	ft_printf("Total data = %i \n", result6);
	printf("%s----------------------------\n%s", RED, END);
	
	int x = '\0';
	int *ptr = &x;
	int *ptr2 = NULL;
	printf("%sTESTING ---> %%p \n%s", GREEN, END);
int totaldata = printf("Function printf = %p\n null pointer = %p\n", ptr, ptr2);
	printf("Total data printf= %d \n", totaldata);
	ft_printf("Total data = %i \n", totaldata);
int result7 = ft_printf("My function = %p \n null pointer = %p \n", ptr, ptr2);
	printf("Total data = %i \n", result7);
	ft_printf("Total data = %i \n", result7);
	printf("%s----------------------------\n%s", RED, END);

	printf("%sTESTING ---> %% \n%s", GREEN, END);
	printf("Function printf = %% \n");
	int result8 = ft_printf("My function = %% \n");
	printf("Total data = %i \n", result8);
	ft_printf("Total data = %i \n", result8);
	printf("%s----------------------------\n%s", RED, END);
	printf("%sPARECE QUE FUNCIONA --->%s", GREEN, END);


	ft_printf("%", result8);
}*/
