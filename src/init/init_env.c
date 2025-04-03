/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/28 19:07:30 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*find_env_var(t_env **env, char *key)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	add_essential(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	*new_node;

	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	tmp->next = new_node;
	new_node->next = NULL;
}

void	set_essential(t_env **env)
{
	t_env	*tmp;
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		return ;
	}
	tmp = *env;
	while (tmp)
	{
		if (!find_env_var(env, "PATH"))
			add_essential(env, "PATH", "/usr/local/bin:/usr/bin:/bin");
		else if (!find_env_var(env, "HOME"))
			add_essential(env, "HOME", "/home");
		else if (!find_env_var(env, "PWD"))
			add_essential(env, "PWD", dir);
		tmp = tmp->next;
	}
	free (dir);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*new_node;
	t_env	*last_node;
	size_t	equal_pos;
	int		i;

	head = NULL;
	last_node = NULL;
	i = 0;
	while (env[i])
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return (NULL);
		equal_pos = ft_strcspn(env[i], "=");
		if (equal_pos == ft_strlen(env[i])) //si no encuentra un = se lo salta y pasa al siguiente str
			continue ;
		new_node->key = ft_substr(env[i], 0, equal_pos);
		new_node->value = ft_strdup(env[i] + equal_pos + 1);
		new_node->next = NULL;
		if (!head)
			head = new_node;
		else
		{
			last_node->next = new_node;
		}
		last_node = new_node;
		i++;
	}
	set_essential(&head);
	return (head);
}
