/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:15:23 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/03 18:15:28 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static 	char *find_env(char *token_str, t_env *env, t_token *token)
{
	int		len;
	char	*expanded;
	char	*statik;
	int		i;

	len = 0;
	expanded = NULL;
	i = 0;
	while (token->value[len] && token->value[len] != '$')
		len ++;
	statik = (char *)malloc(sizeof(char) * (len + 1));
	statik[len] = '\0';
	while (i < len)
	{
		statik[i] = token->value[i];
		i++;
	}
	while (env)
	{	
		if (!strcmp(token_str, env->key))
			expanded = env->value;
		env = env->next;
	}
	free(token->value);
	token->value = ft_strjoin(statik, expanded);
	free(statik);
	return (token->value);
}

static void	print_exit_status(char *token_str, int exit_status)
{
	int	i;

	i = 0;
	while (token_str[i])
	{
		if(token_str[i] == '$')
		{
			ft_printf("%d", exit_status);
			return ;
		}
		else
		{
			ft_printf("%c", token_str[i]);
			i++;
		}
	}
}

void	ft_expansor(t_token *token, t_env *env, int exit_status)
{
	char	*token_str;
	t_token	*tmp;
	int		i;

	tmp = token;
	while (tmp)
	{
		token_str = tmp->value;
		i = 0;
		while (token_str[i])
		{
			if(token_str[i] == '$')
			{
				if (token_str[i + 1] == '?')
				{
					print_exit_status(token_str, exit_status);
					return ;
				}
				else
				{
					token_str = find_env(token_str + i + 1, env, tmp);
				}
			}
			i++;
		}
		tmp = tmp->next;
	}
}

