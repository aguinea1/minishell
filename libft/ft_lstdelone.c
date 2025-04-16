/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*
#include <stdio.h>
#include <string.h>
void    del(void *content)
{
	free(content);
}

int main(void)
{
	t_list  *head = malloc(sizeof(t_list));
	char    *str = "Viva España";

	head->content = malloc(sizeof(char) + strlen(str)+1);
	strcpy(head->content, str);
	head->next = NULL;
	printf("%s\n", head->content);
	ft_lstdelone(head, del);
	return 0;
}*/
