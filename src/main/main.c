/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/16 17:04:14 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_lst;
	t_env	*exprt_lst;
	int		exit_status;

	if (ac != 1)
		return (err_out("minishell: ", av[1],
				": No such file or directory", ""), 127);
	if (!env | !*env)
	{
		env_lst = init_no_env(0);
		exprt_lst = init_no_env(1);
	}
	else
	{
		env_lst = init_env(env);
		exprt_lst = init_env(env);
	}
	disable_signal_echo();
	exit_status = minishell_loop(env_lst, exprt_lst);
	return (exit_status);
}
