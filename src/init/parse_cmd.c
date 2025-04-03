/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 21:09:03 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/28 19:07:33 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	env_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**env_to_array(t_env *env)
{
	int		size;
	int		i;
	char	**array;
	char	*env_var;
	t_env	*tmp;

	tmp = env;
	size = env_size(env);
	array = malloc(sizeof(char *) * (size + 1));
	if (!array)
		return (NULL);
	i = 0;
	while (tmp)
	{
		env_var = malloc(ft_strlen(tmp->key) + ft_strlen(tmp->value) + 2);
		if (!env_var)
			return (NULL);
		ft_strcpy(env_var, tmp->key);
		ft_strcat(env_var, "=");
		ft_strcat(env_var, tmp->value);
		array[i++] = env_var;
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}

int	check_acces(char **dir, char *full_path)
{
	if (access(full_path, F_OK) == 0)
	{
		ft_free_array(dir);
		return (0);
	}
	free (full_path);
	return (1);
}

char	*get_path(char **env, t_command *cmd)
{
	int		i;
	int		j;
	char	**dir;
	char	*pre_path;
	char	*full_path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	dir = ft_split(env[i] + 5, ':');
	j = 0;
	while (dir[j])
	{
		pre_path = ft_strjoin(dir[j], "/");
		full_path = ft_strjoin(pre_path, cmd->args[0]);
		free(pre_path);
		if (check_acces(dir, full_path) == 0)
			return (full_path);
		j++;
	}
	ft_free_array(dir);
	return (NULL);
}

void	get_cmd(t_command *cmd, t_env *env)
{
	if (!cmd->args)
		return ;
	cmd->env_array = env_to_array(env);
	if (ft_strchr(cmd->args[0], '/'))
		cmd->path = ft_strdup(cmd->args[0]);
	else
		cmd->path = get_path(cmd->env_array, cmd);
}
