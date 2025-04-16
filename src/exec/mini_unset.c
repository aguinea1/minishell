/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:44 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	remove_node(t_env **lst, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	prev = NULL;
	tmp = *lst;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*lst = (*lst)->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	mini_unset(t_command *cmd, t_env **env, t_env **export, int n_cmds)
{
	int		i;

	if (n_cmds > 1)
		return (0);
	if (!cmd->args[1])
		return (ft_putendl_fd("unset: not enough arguments", 2), 1);
	i = 1;
	while (cmd->args[i])
	{
		remove_node(env, cmd->args[i]);
		remove_node(export, cmd->args[i]);
		i++;
	}
	return (0);
}
