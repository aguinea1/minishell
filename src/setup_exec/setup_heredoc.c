/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:29:10 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 16:38:24 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_and_out(t_redirection *redir)
{
	free(redir->hd_filename);
	err_out("minishell: heredoc: ", strerror(errno), NULL, NULL);
}

char	*get_hd_filename(t_shell *shell)
{
	char	*num;
	char	*filename;

	num = ft_itoa(shell->hd_count);
	filename = ft_strjoin("/tmp/heredoc_", num);
	free(num);
	return (filename);
}

void	open_heredoc(t_redirection *redir, t_shell *shell,
		int exit_status, t_env *env)
{
	int		tmp_fd;
	char	*line;
	char	*delimiter;

	shell->here_doc = 1;
	delimiter = redir->file;
	redir->hd_filename = get_hd_filename(shell);
	tmp_fd = open(redir->hd_filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (tmp_fd == -1)
		free_and_out(redir);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
			break ;
		line = line_expanded(line, env, exit_status);
		ft_putstr_fd(line, tmp_fd);
		ft_putstr_fd("\n", tmp_fd);
		free(line);
	}
	close(tmp_fd);
	redir->fd_in = open(redir->hd_filename, O_RDONLY);
	if (redir->fd_in == -1)
		free_and_out(redir);
}
