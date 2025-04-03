/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:28:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 15:28:21 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_pipes * 2)
	{
		close(shell->pipes[i]);
		i++;
	}
}

void	close_fds(t_command *cmd, t_shell *shell)
{
	t_command		*c_tmp;
	t_redirection	*r_tmp;

	c_tmp = cmd;
	while (c_tmp)
	{
		r_tmp = c_tmp->redirs;
		while (r_tmp)
		{
			if (r_tmp->fd_in == -1 || r_tmp->type == REDIR_IN)
				close(r_tmp->fd_in);
			if (r_tmp->fd_out == -1 || r_tmp->type == REDIR_OUT
				|| r_tmp->type == APPEND)
				close(r_tmp->fd_out);
			r_tmp = r_tmp->next;
		}
		c_tmp = c_tmp->next;
	}
	close_pipes(shell);
}
