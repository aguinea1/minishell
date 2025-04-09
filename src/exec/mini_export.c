/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:29:58 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/08 14:23:08 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_export_lonely(t_env *export)
{
	t_env	*tmp;

	tmp = export;
	if (!export)
		return ;
	ft_bubble(export);
	while (tmp)
	{
		if (tmp->value)
		{
			if (!tmp->value)
				ft_printf("declare -x %s\n", tmp->key);
			else
				ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		}
		else
		{
			ft_printf("declare -x %s\n", tmp->key);
		}
		tmp = tmp->next;
	}
}

static int	keycmp(char *key, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && key[i] && arg[i] == key[i])
		i++;
	if ((!arg[i] || arg[i] == '=') && !key[i])
		return (0);
	return (1);
}

static int	update_if_repeated(t_env *export, char *arg, int value_start)
{
	t_env	*tmp;
	char	*temp_value;

	tmp = export;
	while (tmp)
	{
		if (keycmp(tmp->key, arg) == 0)
		{
			if (arg[value_start - 1] != '=')
				return (1);
			temp_value = ft_strdup(arg + value_start);
			free(tmp->value);
			tmp->value = temp_value;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	create_and_add_node(t_env *export, char *arg,
			int value_start, int flag)
{
	char	*temp_value;
	t_env	*new_node;

	if (should_skip_creation(arg, value_start, flag))
		return (1);
	temp_value = get_export_value(arg, value_start);
	if (!temp_value && arg[value_start - 1] == '=')
		return (0);
	new_node = init_new_node(arg, value_start, temp_value);
	if (!new_node)
		return (1);
	append_to_list(export, new_node);
	return (1);
}

int	mini_export(t_command *cmd, t_env *export, int flag)
{
	char	*arg;
	int		i;
	int		value_start;

	i = 1;
	if (!export || !cmd || !cmd->args || !cmd->args[1])
	{
		if (flag == 1)
			ft_export_lonely(export);
		return (1);
	}
	while (cmd->args[i])
	{
		arg = cmd->args[i];
		value_start = find_key(arg);
		if (!update_if_repeated(export, arg, value_start))
			create_and_add_node(export, arg, value_start, flag);
		i++;
	}
	return (1);
}
