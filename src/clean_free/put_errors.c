/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:28:26 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:10:11 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	err_out(char *str1, char *str2, char *str3, char *str4)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putstr_fd(str3, STDERR_FILENO);
	ft_putendl_fd(str4, STDERR_FILENO);
}
