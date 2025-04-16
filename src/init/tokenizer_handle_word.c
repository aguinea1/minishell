/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_handle_word.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static int	handle_export_quotes(char *input, int *i,
	int *in_quote, char *quote_char)
{
	if (!*in_quote && (input[*i] == '\'' || input[*i] == '"'))
	{
		*in_quote = 1;
		*quote_char = input[(*i)++];
		return (1);
	}
	if (*in_quote && input[*i] == *quote_char)
	{
		*in_quote = 0;
		(*i)++;
		return (1);
	}
	return (0);
}

static int	append_char(char **arg, char c)
{
	char	*temp;
	int		len;

	len = ft_strlen(*arg);
	temp = malloc(len + 2);
	if (!temp)
		return (0);
	ft_strcpy(temp, *arg);
	temp[len] = c;
	temp[len + 1] = '\0';
	free(*arg);
	*arg = temp;
	return (1);
}

int	extract_export_arg(t_token **token, char *input, int *i)
{
	char	*arg;
	int		in_quote;
	char	quote_char;

	in_quote = 0;
	quote_char = 0;
	arg = ft_calloc(1, sizeof(char));
	if (!arg)
		return (0);
	while (input[*i])
	{
		if (handle_export_quotes(input, i, &in_quote, &quote_char))
			continue ;
		if (!in_quote && (input[*i] == ' ' || input[*i] == '\t'))
			break ;
		if (!append_char(&arg, input[*i]))
			return (free(arg), 0);
		(*i)++;
	}
	add_token(token, arg, WORD);
	free(arg);
	return (1);
}

void	handle_word(t_token **token, char *input, int *i, int *export_mode)
{
	if (!*token)
	{
		if (ft_strncmp(&input[*i], "export", 6) == 0
			&& (input[*i + 6] == ' ' || input[*i + 6] == '\0'))
			*export_mode = 1;
	}
	if (*export_mode)
		extract_export_arg(token, input, i);
	else
		extract_word(token, input, i);
}
