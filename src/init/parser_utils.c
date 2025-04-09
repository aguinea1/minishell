/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:47:25 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/08 16:39:05 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_redirection	*create_redirection(char **tokens, int *i)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	if (!ft_strcmp(tokens[*i], ">"))
		redir->type = REDIR_OUT;
	else if (!ft_strcmp(tokens[*i], ">>"))
		redir->type = APPEND;
	else if (!ft_strcmp(tokens[*i], "<"))
		redir->type = REDIR_IN;
	else if (!ft_strcmp(tokens[*i], "<<"))
		redir->type = HEREDOC;
	(*i)++;
	redir->file = ft_strdup(tokens[*i]);
	return (redir);
}

void	add_redir(t_command *cmd, char **tokens, int *i)
{
	t_redirection	*redir;
	t_redirection	*tmp;

	redir = create_redirection(tokens, i);
	if (!redir)
		return ;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		tmp = cmd->redirs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = redir;
	}
}
