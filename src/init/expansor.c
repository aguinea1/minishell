/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/27 13:29:34 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	find_env(char *token_str, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if(!ft_strcmp(token_str, tmp->key))
			ft_printf("%s", tmp->value);
		tmp = tmp->next;
	}
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
			i = i + 2;
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
	int		i;

	while (token)
	{
		token_str = token->value;
		i = 0;
		while (token_str[i])
		{
			if(token_str[i] == '$')
			{
				if (token_str[i + 1] == '?')
						print_exit_status(token_str, exit_status);
				else
					find_env(token_str + i + 1, env);
			}
			i++;
		}
		token = token->next;
	}
}
