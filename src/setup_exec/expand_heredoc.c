/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:04:29 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 16:58:22 by arcebria         ###   ########.fr       */
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

char	*line_expanded(char *line, t_env *env, int exit_status)
{
	char	*result;
	char	*tmp;
	char	*addition;
	int		i;

	result = ft_strdup("");
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (line[i] == '?')
				addition = expand_status(exit_status, &i);
			else
				addition = expand_variable(line, &i, env);
		}
		else
			addition = expand_text(line, &i);
		tmp = ft_strjoin(result, addition);
		free(result);
		free(addition);
		result = tmp;
	}
	return (result);
}
