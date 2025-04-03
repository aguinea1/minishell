/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_echo_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:28 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 15:27:29 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	mini_pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		return (1);
	}
	ft_printf("%s\n", dir);
	free(dir);
	return (0);
}

int	mini_echo(char **args)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	while (!ft_strncmp(args[i], "-n", 2))
	{
		if (ft_strspn(args[i], "-n") == ft_strlen(args[i]))
		{
			new_line = 0;
			i++;
		}
		else
			break ;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[i + 1])
			ft_printf(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (0);
}

int	mini_env(t_env *env_lst)
{
	t_env	*tmp;

	if (!env_lst)
		exit (1);
	tmp = env_lst;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	return (0);
}
