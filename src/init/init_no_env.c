/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:14:22 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/08 17:05:26 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_env	*create_oldpwd(void)
{
	t_env	*oldpwd;

	oldpwd = malloc(sizeof(t_env));
	if (!oldpwd)
		return (NULL);
	oldpwd->key = ft_strdup("OLDPWD");
	oldpwd->value = ft_strdup("");
	oldpwd->next = NULL;
	return (oldpwd);
}

static t_env	*create_underscore_node(t_env *oldpwd)
{
	t_env	*no_c;

	no_c = malloc(sizeof(t_env));
	if (!no_c)
		return (NULL);
	no_c->key = ft_strdup("_");
	no_c->value = ft_strdup("/usr/bin/env");
	no_c->next = oldpwd;
	return (no_c);
}

static t_env	*create_shlvl_node(t_env *no_c)
{
	t_env	*shlvl;

	shlvl = malloc(sizeof(t_env));
	if (!shlvl)
		return (NULL);
	shlvl->key = ft_strdup("SHLVL");
	shlvl->value = ft_strdup("1");
	shlvl->next = no_c;
	return (shlvl);
}

t_env	*init_no_env(int flag)
{
	t_env	*pwd;
	t_env	*shlvl;
	t_env	*no_c;
	t_env	*oldpwd;

	oldpwd = NULL;
	if (flag == 1)
		oldpwd = create_oldpwd();
	no_c = create_underscore_node(oldpwd);
	if (!no_c)
		return (NULL);
	shlvl = create_shlvl_node(no_c);
	if (!shlvl)
		return (NULL);
	pwd = malloc(sizeof(t_env));
	if (!pwd)
		return (NULL);
	pwd->key = ft_strdup("PWD");
	pwd->value = getcwd(NULL, 0);
	pwd->next = shlvl;
	return (pwd);
}
