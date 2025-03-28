/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:22:21 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/27 12:22:35 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	err_out(char *str1, char *str2, char *str3, char *str4)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putstr_fd(str3, STDERR_FILENO);
	ft_putendl_fd(str4, STDERR_FILENO);
	return ;
}
