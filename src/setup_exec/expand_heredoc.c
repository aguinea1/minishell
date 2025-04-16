/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*search_value(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (tmp->value)
				return (tmp->value);
			else
				return ("");
		}
		tmp = tmp->next;
	}
	return ("");
}

char	*expand_text(char *line, int *i)
{
	char	*text;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != '$')
		(*i)++;
	text = ft_substr(line, start, *i - start);
	return (text);
}

char	*expand_variable(char *line, int *i, t_env *env)
{
	char	*key;
	char	*value;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != ' ' && line[*i] != '$'
		&& line[*i] != '\'' && line[*i] != '\"')
		(*i)++;
	key = ft_substr(line, start, *i - start);
	value = search_value(key, env);
	free(key);
	return (ft_strdup(value));
}

char	*expand_status(int exit_status, int *i)
{
	char	*status;

	status = ft_itoa(exit_status);
	(*i)++;
	return (status);
}

char	*check_to_expand(char *line, int *i, t_env *env, int exit_status)
{
	char	*addition;

	if (line[*i] == '$')
	{
		(*i)++;
		if (line[*i] == '?')
			addition = expand_status(exit_status, i);
		else
			addition = expand_variable(line, i, env);
	}
	else
		addition = expand_text(line, i);
	return (addition);
}
