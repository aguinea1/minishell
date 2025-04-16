/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_token	*find_last(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

int	handle_quotes(t_token **token, char *input, int *i, int *flag)
{
	if (input[*i] == '"' || input[*i] == '\'')
	{
		if (input[*i] == '\'')
			(*flag) = 1;
		if (extract_quoted_token(token, input, i))
			return (1);
	}
	return (0);
}

static int	handle_pipe(t_token **token, char *input, int *i)
{
	char	op1[2];

	if (input[*i] != '|' && input[*i] != '&')
		return (0);
	else
	{
		op1[0] = input[*i];
		op1[1] = '\0';
		if (input[*i] == '&')
			add_token(token, op1, AMPERSAND);
		else
			add_token(token, op1, PIPE);
		(*i)++;
	}
	return (1);
}

int	handle_operator_token(t_token **token, char *input, int *i)
{
	if (handle_pipe(token, input, i))
		return (1);
	if (handle_redirection(token, input, i))
		return (1);
	return (0);
}

int	handle_redirection(t_token **token, char *input, int *i)
{
	if (input[*i] != '<' && input[*i] != '>')
		return (0);
	if (input[*i + 1] == input[*i])
	{
		if (input[*i] == '<')
			add_token(token, "<<", HEREDOC);
		else
			add_token(token, ">>", APPEND);
		*i += 2;
	}
	else
	{
		if (input[*i] == '<')
			add_token(token, "<", REDIR_IN);
		else
			add_token(token, ">", REDIR_OUT);
		(*i)++;
	}
	return (1);
}
