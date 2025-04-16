/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*line_expanded(char *line, t_env *env, int exit_status)
{
	char	*result;
	char	*tmp;
	char	*addition;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (line[i])
	{
		addition = check_to_expand(line, &i, env, exit_status);
		if (!addition)
			return (free(result), free(line), NULL);
		tmp = ft_strjoin(result, addition);
		free(result);
		free(addition);
		if (!tmp)
			return (free(line), NULL);
		result = tmp;
	}
	return (free(line), result);
}

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
	if (line)
		free(line);
	close(tmp_fd);
	redir->fd_in = open(redir->hd_filename, O_RDONLY);
	if (redir->fd_in == -1)
		free_and_out(redir);
}
