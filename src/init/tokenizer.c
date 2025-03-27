/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:54:26 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/21 11:21:44 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*find_last(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void	add_token(t_token **token, char *value, int type, int *i)
{
	t_token	*new_node;
	t_token	*last_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return ;
	new_node->next = NULL;
	new_node->type = type;
	new_node->value = ft_strdup(value);
	if (!*token)
		*token = new_node;
	else
	{
		last_node = find_last(*token);
		last_node->next = new_node;
	}
	if (new_node->type == PIPE || new_node->type == AMPERSAND
		|| new_node->type == REDIR_IN || new_node->type == REDIR_OUT
		|| new_node->type == APPEND || new_node->type == HEREDOC)
		(*i)++;
	if (new_node->type == APPEND || new_node->type == HEREDOC)
		(*i)++;

}

int	extract_quoted_token(t_token **token, char *input, int *i)
{
	int		quote;
	int		start;
	int		len;
	char	*word;

	quote = input[*i];
	start = *i + 1;
	len = 0;
	while (input[start + len] != quote && input[start + len])
		len++;
	if (!input[start + len])
	{
		ft_putstr_fd("Open quotation marks\n", 2);
		*i = start + len;
		return (1);
	}
	word = ft_substr(input, start, len);
	add_token(token, word, WORD, i);
	free(word);
	*i = start + len + 1;
	return (0);
}

void	extract_word(t_token **token, char *input, int *i)
{
	int		start;
	int		len;
	char	*word;

	start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_isspecial(input[*i]))
		(*i)++;
	len = *i - start;
	if (len > 0)
	{
		word = ft_substr(input, start, len);
		add_token(token, word, WORD, i);
		free (word);
	}
}

t_token	*tokenizer(char *input, t_heredoc *here)
{
	t_token	*token;
	int		i;

	token = NULL;
	i = 0;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '|')
			add_token(&token, "|", PIPE, &i);
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_token(&token, "<<", HEREDOC, &i);
				here->num++;
			}
			else
				add_token(&token, "<", REDIR_IN, &i);
		}
		else if (input[i] == '>')
		{
			if (input[i + 1] == '>')
				add_token(&token, ">>", APPEND, &i);
			else
				add_token(&token, ">", REDIR_OUT, &i);
		}
		else if (input[i] == '\"' || input[i] == '\'')
		{
			if (extract_quoted_token(&token, input, &i))
				return (free_tokens(&token), NULL);
		}
		else
			extract_word(&token, input, &i);
	}
	return (token);
}
