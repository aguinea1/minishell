/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:54:26 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/03 14:02:42 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
t_token *find_last(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

void add_token(t_token **token, char *value, t_token_type type)
{
	t_token *new_node = malloc(sizeof(t_token));
	if (!new_node)
		return;
	new_node->next = NULL;
	new_node->type = type;
	new_node->value = ft_strdup(value);

	if (!*token)
		*token = new_node;
	else
	{
		t_token *last_node = find_last(*token);
		last_node->next = new_node;
	}
}

int extract_quoted_token(t_token **token, char *input, int *i)
{
	char quote = input[*i];
	int start = ++(*i);

	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i]) // Si no se cerró la comilla
	{
		ft_putstr_fd("Error: Open quotation marks\n", 2);
		return (1);
	}

	char *word = ft_substr(input, start, *i - start);
	add_token(token, word, WORD);
	free(word);
	(*i)++; // Avanzar después de la comilla de cierre
	return (0);
}

int	extract_word(t_token **token, char *input, int *i)
{
	int start = *i;
	while (input[*i] && !ft_isspace(input[*i]) && !ft_isspecial(input[*i]))
		(*i)++;
	int len = *i - start;
	if (len > 0)
	{
		char *word = ft_substr(input, start, len);
		add_token(token, word, WORD);
		free(word);
		return (1);
	}
	return (0);
}

t_token *tokenizer(char *input, t_env *env, int exit_status)
{
	t_token *token = NULL;
	int i = 0;

	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (input[i] == '|' || input[i] == '&')
		{
			if (input[i + 1] == input[i]) // || o &&
			{
				char op[3] = {input[i], input[i], '\0'};
				add_token(&token, op, (input[i] == '&') ? AMPERSAND : OR);
				i += 2; // Avanzar dos posiciones
			}
			else
			{
				char op[2] = {input[i], '\0'};
				add_token(&token, op, (input[i] == '&') ? AMPERSAND : PIPE);
				i++; // Avanzar una posición
			}
		}
		else if (input[i] == '<' || input[i] == '>')
		{
			if (input[i + 1] == input[i]) // << o >>
			{
				add_token(&token, (input[i] == '<') ? "<<" : ">>", (input[i] == '<') ? HEREDOC : APPEND);
				i += 2;
			}
			else
			{
				add_token(&token, (input[i] == '<') ? "<" : ">", (input[i] == '<') ? REDIR_IN : REDIR_OUT);
				i++;
			}
		}
		else if (input[i] == '"' || input[i] == '\'')
		{
			if (extract_quoted_token(&token, input, &i))
				return (free_tokens(&token), NULL);
		}
		else
		{
			if (extract_word(&token, input, &i) == 1)
				ft_expansor(token, env, exit_status);
		}
	}
	return (token);
}


