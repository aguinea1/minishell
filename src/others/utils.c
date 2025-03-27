/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:35:02 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/24 15:38:15 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->env_array = NULL;
	cmd->path = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_redir_utils(t_redirection *tmp,t_command *cmd, t_redirection *redir)
{
	tmp = cmd->redirs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = redir;
}
