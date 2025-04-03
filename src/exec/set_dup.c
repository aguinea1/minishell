/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:55 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 15:27:56 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	dup_files(t_redirection *redir, t_shell *shell)
{
	int	in_fd;
	int	out_fd;

	if (redir)
	{
		if (shell->child == 0)
			return (dup_first_child(redir, shell));
		if (shell->child == shell->n_pipes)
			return (dup_last_child(redir, shell));
		return (dup_n_child(redir, shell));
	}
	in_fd = -1;
	out_fd = -1;
	if (shell->child != 0)
		in_fd = shell->pipes[2 * shell->child - 2];
	if (shell->child != shell->n_pipes)
		out_fd = shell->pipes[2 * shell->child + 1];
	if (in_fd != -1 && dup2(in_fd, STDIN_FILENO) == -1)
		return (1);
	if (out_fd != -1 && dup2(out_fd, STDOUT_FILENO) == -1)
		return (1);
	return (0);
}

int	dup_one_cmd(t_redirection *redir)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN || tmp->type == HEREDOC)
		{
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
				return (1);
			close(tmp->fd_in);
		}
		else if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
				return (1);
			close(tmp->fd_out);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	set_dup(t_redirection *redir, t_shell *shell)
{
	if (shell->n_cmds == 1)
	{
		if (dup_one_cmd(redir) == 1)
			return (1);
	}
	else if (shell->n_cmds > 1)
	{
		if (dup_files(redir, shell) == 1)
			return (1);
	}
	return (0);
}
