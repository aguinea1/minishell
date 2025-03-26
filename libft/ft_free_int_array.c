/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_int_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:38:53 by arcebria          #+#    #+#             */
/*   Updated: 2025/01/27 20:24:09 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_int_array(int **array, int size)
{
	int		i;

	i = 0;
	if (!array)
		return ;
	while (i < size)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}
