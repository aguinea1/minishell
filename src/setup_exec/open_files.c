/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:18:35 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 16:40:58 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	open_infile(t_redirection *redir)
{
	redir->fd_in = open(redir->file, O_RDONLY, 644);
	if (redir->fd_in == -1)
		err_out("minishell: ", redir->file, ": ", strerror(errno));
}

void	open_outfile(t_redirection *redir, int append)
{
	if (append == 0)
		redir->fd_out = open(redir->file, O_CREAT
				| O_WRONLY | O_TRUNC, 0664);
	else if (append == 1)
		redir->fd_out = open(redir->file, O_CREAT
				| O_WRONLY | O_APPEND, 0664);
	if (redir->fd_out == -1)
		strerror(errno);
}

void	check_type(t_redirection *redir, t_shell *shell, int stat, t_env *env)
{
	if (redir->type == REDIR_IN)
		open_infile(redir);
	else if (redir->type == HEREDOC)
	{
		open_heredoc(redir, shell, stat, env);
		shell->hd_count++;
	}
	else if (redir->type == REDIR_OUT)
		open_outfile(redir, 0);
	else if (redir->type == APPEND)
		open_outfile(redir, 1);
}

t_shell	*setup_exec(t_command *cmd, int exit_status, t_env *env)
{
	t_shell			*shell;
	t_command		*c_tmp;
	t_redirection	*r_tmp;

	shell = init_shell(cmd);
	c_tmp = cmd;
	while (c_tmp)
	{
		r_tmp = c_tmp->redirs;
		while (r_tmp)
		{
			check_type(r_tmp, shell, exit_status, env);
			r_tmp = r_tmp->next;
		}
		c_tmp = c_tmp->next;
	}
	create_pipes(shell);
	return (shell);
}
