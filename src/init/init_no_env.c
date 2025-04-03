/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_no_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:14:22 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/03 18:14:27 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*init_no_env(int flag)
{
	t_env	*pwd;
	t_env	*shlvl;
	t_env	*oldpwd;
	t_env	*no_c;


	if (flag == 1)
	{	
		oldpwd = malloc(sizeof(t_env));
		if (!oldpwd)
			return(NULL);
		oldpwd->key = ft_strdup("OLDPWD");
		oldpwd->value = ft_strdup("");
		oldpwd->next = NULL;
	}

	no_c = malloc(sizeof(t_env));
	if (!no_c	)
		return(NULL);
	no_c->key = ft_strdup("_");
	no_c->value = ft_strdup("/usr/bin/env");
	if (flag == 1)
		no_c->next = oldpwd;
	else
		no_c->next = NULL;

	shlvl = malloc(sizeof(t_env));
	if (!shlvl)
		return(NULL);
	shlvl->key = ft_strdup("SHLVL");
	shlvl->value = ft_strdup("1");
	shlvl->next = no_c;

	pwd = malloc(sizeof(t_env));
	if (!pwd)
		return(NULL);
	pwd->key = ft_strdup("PWD");
	pwd->value = getcwd(NULL, 0);
	pwd->next = shlvl;

	return (pwd);
}
