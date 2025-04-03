/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:27:17 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 15:27:18 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cd_home(void)
{
	char	*home;

	home = getenv("HOME");
	if (home)
	{
		if (chdir(home) != 0)
			return (perror("cd"), 1);
	}
	else
		return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	return (0);
}

int	cd_oldpwd(char *oldpwd)
{
	if (oldpwd)
	{
		ft_printf("~%s\n", oldpwd);
		if (chdir(oldpwd) != 0)
			return (perror("cd"), 1);
	}
	else
		return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
	return (0);
}

int	cd_path(char *path)
{
	char	*test_cwd;

	if (chdir(path) != 0)
		return (perror("cd"), 1);
	else
	{
		test_cwd = getcwd(NULL, 0);
		if (!test_cwd)
		{
			err_out("cd: error retrieving current directory: ",
				"getcwd: cannot access parent directories: ",
				strerror(errno), "");
			return (cd_home());
		}
		free(test_cwd);
	}
	return (0);
}

int	mini_cd(char **args, t_env *env_lst, int n_cmds)
{
	char	*oldpwd;
	char	*newpwd;
	int		exit_status;

	exit_status = 0;
	if (n_cmds > 1)
		return (0);
	oldpwd = get_oldpwd(env_lst);
	newpwd = getcwd(NULL, 0);
	if (!args[1])
		exit_status = cd_home();
	else if (ft_strcmp(args[1], "-") == 0)
		exit_status = cd_oldpwd(oldpwd);
	else
		exit_status = cd_path(args[1]);
	return (update_env(env_lst, "OLDPWD", newpwd), free(newpwd), exit_status);
}
