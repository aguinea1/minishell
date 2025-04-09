/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:31:39 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/08 17:22:03 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	handle_word(t_token **token, char *input, int *i,
			t_env *env, int exit_status)
{
	if (extract_word(token, input, i) == 1)
		ft_expansor(*token, env, exit_status);
}

int	handle_quotes(t_token **token, char *input, int *i)
{
	if (input[*i] == '"' || input[*i] == '\'')
	{
		if (extract_quoted_token(token, input, i))
			return (1);
	}
	return (0);
}

int	handle_operator_token(t_token **token, char *input, int *i)
{
	if (handle_pipe_ampersand(token, input, i))
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

int	handle_pipe_ampersand(t_token **token, char *input, int *i)
{
	char	op[3];
	char	op1[2];

	if (input[*i] != '|' && input[*i] != '&')
		return (0);
	if (input[*i + 1] == input[*i])
	{
		op[0] = input[*i];
		op[1] = input[*i];
		op[2] = '\0';
		if (input[*i] == '&')
			add_token(token, op, AMPERSAND);
		else
			add_token(token, op, OR);
		*i += 2;
	}
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
