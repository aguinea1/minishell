/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 12:38:45 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/27 13:19:58 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!dir)
	{
		ft_putstr_fd("pwd: error retrieving current directory\n", 2);
		return ;
	}
	ft_printf("%s\n", dir);
	free(dir);
}

void	cd_home(char *home)
{
	home = getenv("HOME");
	if (home)
	{
		if (home)
		{
			if (chdir(home) != 0)
				perror("cd");
		}
		else
			ft_putstr_fd("cd: HOME not set\n", 2);
	}
}

void	cd_oldpwd(char *oldpwd)
{
	if (oldpwd)
	{
		ft_printf("~%s\n", oldpwd);
		if (chdir(oldpwd) != 0)
			perror("cd");
	}
	else
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
}

void	update_env(t_env *env_lst, char *key, char *new_value)
{
	t_env	*tmp;

	if (!env_lst || !key || !new_value)
		return ;
	tmp = env_lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(new_value);
			return ;
		}
		tmp = tmp->next;
	}
}

char	*get_oldpwd(t_env *env)
{
	char	*pwd;
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "OLDPWD"))
			return (pwd = tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	cd(char **args, t_env *env_lst)
{
	char	*home;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = get_oldpwd(env_lst);
	newpwd = getcwd(NULL, 0);
	home = getenv("HOME");
	if (!args[1])
		cd_home(home);
	else if (ft_strcmp(args[1], "-") == 0)
		cd_oldpwd(oldpwd);
	else
	{
		if (chdir(args[1]) != 0)
			perror("cd");
	}
	update_env(env_lst, "OLDPWD", newpwd);
	free(newpwd);
}

//////////////////////////////////////////////////////////////////////////////

void	echo(char **args)
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
}


/////////////////////////////////////////////////////////////////////////////
void	ft_env(t_env *env_lst)
{
	t_env	*tmp;

	tmp = env_lst->next;
	if (!env_lst)
		return ;
	ft_printf("%s=%s\n", env_lst->key, env_lst->value);
	while (tmp)
	{

		ft_printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

static void	ft_export_lonely(t_env *export)
{
	t_env	*tmp;

	tmp = export->next;
	if (!export)
		return ;
	while (tmp)
	{
		if (tmp->value[0])
			ft_printf("declare -x %s=%s\n", tmp->key, tmp->value);
		else
			ft_printf("declare -x %s%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}


static int find_key(char *args)
{
	int	i;

	i = 0;
	while (args[i] != '=' && args[i])
		i++;
	return (i + 1);
}
/*
void	ft_export(t_token *token, t_env *export, int flag)
{
	t_env	*tmp;
	int		value_start;
	t_env	*new_node;
	int 	not_new;
	char	*is_equal;

	if(!export || !token)
		return ;
	if (!token->next)
	{
		if (flag == 1)
			ft_export_lonely(export);
		return ;
	}
	token = token->next;
	not_new = 0;
	tmp = export;
	value_start = find_key(token->value);
	is_equal = token->value;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, token->value , value_start - 1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(token->value + value_start);
			not_new = 1;
		}
		tmp = tmp->next;
	}
	if (not_new == 0)
	{
		new_node = malloc(sizeof(t_env));
		if (!new_node)
			return ;
		if (ft_strdup(token->value + value_start)[0] == '\0' && flag == 0 && is_equal[value_start - 1] != '=')
					return ;
		new_node->key = ft_substr(token->value, 0, value_start - 1);
		if (new_node->key == NULL)
		{
			free(new_node);
			return ;
		}
		new_node->value = ft_strdup(token->value + value_start);
		if (new_node->value == NULL)
		{
			    free(new_node->key);
				free(new_node);
				return ;
		}
		new_node->next = NULL;
		tmp = export;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
}*/
void	ft_export(t_token *token, t_env *export, int flag)
{
	t_env	*tmp;
	int		value_start;
	t_env	*new_node;
	char	*is_equal;
	char	*temp_value;

	if (!export || !token)
		return ;
	if (!token->next)
	{
		if (flag == 1)
			ft_export_lonely(export);
		return ;
	}
	token = token->next;
	tmp = export;
	value_start = find_key(token->value);
	is_equal = token->value;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, token->value, value_start - 1) == 0)
		{
			temp_value = ft_strdup(token->value + value_start);
			if (!temp_value)
				return ;
			free(tmp->value);
			tmp->value = temp_value;
			return ;
		}
		tmp = tmp->next;
	}

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;

	temp_value = ft_strdup(token->value + value_start);
	if (!temp_value && flag == 0 && is_equal[value_start - 1] != '=')
	{
		free(new_node);
		return ;
	}
	new_node->key = ft_substr(token->value, 0, value_start - 1);
	if (!new_node->key)
	{
		free(new_node);
		free(temp_value);
		return ;
	}
	new_node->value = temp_value;

	new_node->next = NULL;
	tmp = export;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	ft_unset(t_token *token, t_env *env_lst, t_env *export)
{
	int		len;
	t_env	*tmp;
	t_env	*before;

	if (!token->next)
		return ;
	token = token->next;
	len = find_key(token->value) - 1;
	before = env_lst;
	while (before->next)
	{
		tmp = before->next;
		if (!ft_strncmp(tmp->key, token->value, len))
		{
//			printf("%s\n %s1\n", token->value, tmp->key);
			if (tmp->next)
			{
				before->next = tmp->next;
			}
			else
			{
				before->next = NULL;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				break;
			}
		}
		before = before->next;
	}

	before = export;
	while (before->next)
	{
		tmp = before->next;
		if (!ft_strncmp(tmp->key, token->value, len))
		{
//			printf("%s\n %s1\n", token->value, tmp->key);
			if (tmp->next)
			{
				before->next = tmp->next;
			}
			else
			{
				before->next = NULL;
				break;
			}
		//	free(tmp);
		}
		before = before->next;
	}
	free(tmp->value);
	free(tmp->key);
	free(tmp);
}
