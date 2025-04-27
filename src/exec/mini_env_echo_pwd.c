/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_env_echo_pwd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:28 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/27 14:18:36 by aguinea          ###   ########.fr       */
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

static void	ft_print_echo(char **args, int j)
{
	while (args[j])
	{
		ft_printf("%s", args[j]);
		if (args[j + 1])
			ft_printf(" ");
		j++;
	}
}

int	mini_echo(char **args)
{
	int	i;
	int	new_line;
	int	j;

	i = 1;
	j = 1;
	new_line = 1;
	if (args[i][0] == '-')
	{
		while (args[1][i] && args[1][i] == 'n')
			i++;
		if (args[1][i] == '\0')
		{
			new_line = 0;
			j++;
		}
	}
	ft_print_echo(args, j);
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
