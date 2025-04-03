/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:57:57 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/28 19:07:36 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_command	*init_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->env_array = NULL;
	//cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->redirs = NULL;
	//cmd->redirs->flag_in = 0;
	//cmd->redirs->flag_out = 0;
	cmd->next = NULL;
	return (cmd);
}

char	**token_to_array(t_token *token)
{
	int		count;
	int		i;
	char	**array;
	t_token	*tmp;

	tmp = token;
	count = 0;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	tmp = token;
	i = 0;
	while (i < count)
	{
		array[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

void	add_redir(t_command *cmd, char **tokens, int *i)
{
	t_redirection	*redir;
	t_redirection	*tmp;

	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return ;
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

void	add_args(t_command *cmd, char **token, int *last)
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
	new_args[count] = ft_strdup(token[*last]);
	new_args[count + 1] = NULL;
	if (cmd->args)
		ft_free_array(cmd->args);
	cmd->args = new_args;
}

t_command	*parse_simple_cmd(char **tokens, int *i)
{
	t_command	*cmd;

	if (!ft_strcmp(tokens[0], "|"))
		return (NULL);
	cmd = init_command();
	//cmd->cmd = ft_strdup(tokens[*i]);
	while (tokens[*i] && ft_strcmp(tokens[*i], "|"))
	{
		if (!ft_strcmp(tokens[*i], "<") || !ft_strcmp(tokens[*i], "<<")
			|| !ft_strcmp(tokens[*i], ">") || !ft_strcmp(tokens[*i], ">>"))
			add_redir(cmd, tokens, i);
		else
			add_args(cmd, tokens, i);
		(*i)++;
	}
	return (cmd);
}

t_command	*parse_pipeline(t_token	*token)
{
	t_command	*new_cmd;
	t_command	*head;
	t_command	*current;
	char		**tokens;
	int			i;

	tokens = token_to_array(token);
	head = NULL;
	current = NULL;
	if (!tokens)
		return (NULL);
	i = 0;
	while (tokens[i])
	{
		new_cmd = parse_simple_cmd(tokens, &i);
		if (!new_cmd)
			break ;
		if (!head)
			head = new_cmd;
		else
			current->next = new_cmd;
		current = new_cmd;
		if (tokens[i] && !ft_strcmp(tokens[i], "|"))
			i++;
	}
	ft_free_array(tokens);
	return (head);
}
