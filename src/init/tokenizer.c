/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 18:54:26 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/08 17:22:38 by aguinea          ###   ########.fr       */
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

void	add_token(t_token **token, char *value, t_token_type type)
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
}

int	extract_quoted_token(t_token **token, char *input, int *i)
{
	char	quote;
	int		start;
	char	*word;

	quote = input[*i];
	start = ++(*i);
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (!input[*i])
	{
		ft_putstr_fd("Error: Open quotation marks\n", 2);
		return (1);
	}
	word = ft_substr(input, start, *i - start);
	add_token(token, word, WORD);
	free(word);
	(*i)++;
	return (0);
}

int	extract_word(t_token **token, char *input, int *i)
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
		add_token(token, word, WORD);
		free(word);
		return (1);
	}
	return (0);
}

t_token	*tokenizer(char *input, t_env *env, int exit_status)
{
	t_token	*token;
	int		i;

	i = 0;
	token = NULL;
	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (handle_operator_token(&token, input, &i))
			continue ;
		else if (handle_quotes(&token, input, &i))
			return (free_tokens(&token), NULL);
		else
			handle_word(&token, input, &i, env, exit_status);
	}
	return (token);
}
