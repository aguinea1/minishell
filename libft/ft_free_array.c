/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 13:14:14 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/29 21:48:27 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **array)
{
	int		i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i++]);
	}
	free(array);
	array = NULL;
}
