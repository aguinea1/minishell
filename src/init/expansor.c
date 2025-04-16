/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 20:01:08 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	print_exit_status(t_token *token, int exit_status, int i)
{
	char	*before;
	char	*after;
	char	*status_str;
	char	*temp;
	char	*new_value;

	before = ft_strndup(token->value, i);
	after = ft_strdup(token->value + i + 2);
	status_str = ft_itoa(exit_status);
	temp = ft_strjoin(before, status_str);
	new_value = ft_strjoin(temp, after);
	free(token->value);
	token->value = new_value;
	free(before);
	free(after);
	free(status_str);
	free(temp);
}

static char	*find_env(char *token_str, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(token_str, env->key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static char	*join_expanded_parts(char *before, char *expansion, char *after)
{
	char	*temp;
	char	*new_value;

	temp = ft_strjoin(before, expansion);
	new_value = ft_strjoin(temp, after);
	free(temp);
	return (new_value);
}

static char	*ft_aux_expansor(int j, t_env *env, int i, t_token *tmp)
{
	char	*before;
	char	*var_name;
	char	*after;
	char	*expansion;
	char	*new_value;

	before = ft_strndup(tmp->value, i);
	while (tmp->value[j] && (ft_isalnum(tmp->value[j]) || tmp->value[j] == '_'))
		j++;
	var_name = ft_strndup(tmp->value + i + 1, j - (i + 1));
	after = ft_strdup(tmp->value + j);
	expansion = find_env(var_name, env);
	new_value = join_expanded_parts(before, expansion, after);
	free(tmp->value);
	tmp->value = new_value;
	free(before);
	free(after);
	free(var_name);
	free(expansion);
	return (new_value);
}

void	ft_expansor(t_token *token, t_env *env, int exit_status)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	while (tmp)
	{
		i = 0;
		while (tmp->value && tmp->value[i])
		{
			if (tmp->value[i] == '$')
			{
				if (tmp->value[i + 1] == '?')
					print_exit_status(tmp, exit_status, i);
				else
				{
					ft_aux_expansor(i + 1, env, i, tmp);
					i = -1;
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}
