/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export_create.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:54:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:03:06 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	should_skip_creation(char *arg, int value_start, int flag)
{
	if (flag == 0 && arg[value_start - 1] != '=')
		return (1);
	return (0);
}

char	*get_export_value(char *arg, int value_start)
{
	char	*temp_value;

	temp_value = ft_strdup(arg + value_start);
	if (!temp_value)
		return (NULL);
	if (arg[value_start - 1] == '=' && temp_value[0] == '\0')
	{
		free(temp_value);
		return (ft_strdup(""));
	}
	else if (arg[value_start - 1] != '=')
	{
		free(temp_value);
		return (NULL);
	}
	return (temp_value);
}

t_env	*init_new_node(char *arg, int value_start, char *temp_value, int flag)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(temp_value);
		return (NULL);
	}
	new_node->key = export_key(arg, value_start - 1);
	if (!new_node->key)
	{
		if	(flag == 1)
			err_out("minishell: ", "export: `", arg, "': not a valid identifier");
		free(new_node);
		free(temp_value);
		return (NULL);
	}
	new_node->value = temp_value;
	new_node->next = NULL;
	return (new_node);
}

void	append_to_list(t_env *export, t_env *new_node)
{
	t_env	*tmp;

	tmp = export;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}
