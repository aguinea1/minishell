/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redirection	*create_redirection(t_token **token)
{
	t_redirection	*redir;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (NULL);
	redir->next = NULL;
	if ((*token)->type == REDIR_OUT)
		redir->type = REDIR_OUT;
	else if ((*token)->type == APPEND)
		redir->type = APPEND;
	else if ((*token)->type == REDIR_IN)
		redir->type = REDIR_IN;
	else if ((*token)->type == HEREDOC)
		redir->type = HEREDOC;
	else
		return (NULL);
	*token = (*token)->next;
	redir->file = ft_strdup((*token)->value);
	*token = (*token)->next;
	redir->next = NULL;
	return (redir);
}

void	add_redir(t_command *cmd, t_token **token)
{
	t_redirection	*redir;
	t_redirection	*tmp;

	redir = create_redirection(token);
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

void	add_args(t_command *cmd, t_token **token)
{
	int		count;
	int		i;
	char	**new_args;

	count = 0;
	if (cmd->args)
	{
		while (cmd->args[count])
			count++;
	}
	new_args = malloc(sizeof(char *) * (count + 2));
	if (!new_args)
		return ;
	i = 0;
	while (i < count)
	{
		new_args[i] = ft_strdup(cmd->args[i]);
		i++;
	}
	new_args[count] = ft_strdup((*token)->value);
	new_args[count + 1] = NULL;
	if (cmd->args)
		ft_free_array(cmd->args);
	cmd->args = new_args;
	*token = (*token)->next;
}

t_command	*parse_simple_cmd(t_token **token)
{
	t_command	*cmd;

	if ((*token)->type == PIPE)
		return (NULL);
	cmd = init_command();
	while (*token && (*token)->type != PIPE)
	{
		if ((*token)->type == REDIR_IN || (*token)->type == HEREDOC
			|| (*token)->type == REDIR_OUT || (*token)->type == APPEND)
			add_redir(cmd, token);
		else
			add_args(cmd, token);
	}
	return (cmd);
}

t_command	*parse_pipeline(t_token	*token)
{
	t_command	*head;
	t_command	*current;
	t_command	*new_cmd;

	head = NULL;
	current = NULL;
	while (token)
	{
		new_cmd = parse_simple_cmd(&token);
		if (!new_cmd)
			break ;
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (head);
}
