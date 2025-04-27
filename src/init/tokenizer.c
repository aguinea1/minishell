/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/27 13:27:26 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	is_export_mode(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '>' || input[i] == '<')
		{
			i++;
			if (input[i] == '>' || input[i] == '<')
				i++;
			while (input[i] == ' ' || input[i] == '\t')
				i++;
			while (input[i] && !ft_isspace(input[i]) && !ft_isspecial(input[i]))
				i++;
			continue ;
		}
		if (ft_strncmp(&input[i], "export", 6) == 0
			&& (input[i + 6] == ' ' || input[i + 6] == '\0'))
			return (1);
		else
			return (0);
	}
	return (0);
}

t_token	*tokenizer(char *input, t_env *env, int exit_status)
{
	t_token	*token;
	int		i;
	int		export_mode;
	int		flag_quote;

	i = 0;
	flag_quote = 0;
	token = NULL;
	export_mode = is_export_mode(input);
	while (input[i])
	{
		flag_quote = 0;
		if (input[i] == ' ' || input[i] == '\t')
			i++;
		else if (handle_operator_token(&token, input, &i))
			continue ;
		else if (handle_quotes(&token, input, &i, &flag_quote))
			return (free_tokens(&token), NULL);
		else
			handle_word(&token, input, &i, &export_mode);
		if (!export_mode && !flag_quote)
			ft_expansor(token, env, exit_status);
	}
	return (token);
}
