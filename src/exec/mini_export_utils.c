/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 13:52:25 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/08 14:24:53 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_swap_lst(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	temp_value = a->value;
	temp_key = a->key;
	a->key = b->key;
	a->value = b->value;
	b->key = temp_key;
	b->value = temp_value;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	c1;
	unsigned char	c2;

	while (*s1 && *s2)
	{
		c1 = (unsigned char)*s1;
		c2 = (unsigned char)*s2;
		if (c1 != c2)
			return (c1 - c2);
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void	ft_bubble(t_env *export)
{
	t_env	*tmp;
	t_env	*before;

	before = export;
	tmp = export->next;
	while (tmp)
	{
		if (ft_strcmp(before->key, tmp->key) > 0)
		{
			ft_swap_lst(before, tmp);
			before = export;
			tmp = export->next;
		}
		else
		{
			tmp = tmp->next;
			before = before->next;
		}
	}
}

int	find_key(char *args)
{
	int	i;

	i = 0;
	while (args[i] != '=' && args[i])
		i++;
	return (i + 1);
}

char	*export_key(char *s, int len)
{
	char	*subs;
	int		i;

	if (!s)
		return (NULL);
	subs = malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if ((s[i] >= 'a' && s[i] <= 'z')
			|| (s[i] >= 'A' && s[i] <= 'Z') || s[i] == '_')
			subs[i] = s[i];
		else if (i > 0 && s[i] >= '0' && s[i] <= '9')
			subs[i] = s[i];
		else
		{
			free(subs);
			return (NULL);
		}
		i++;
	}
	subs[len] = '\0';
	return (subs);
}
