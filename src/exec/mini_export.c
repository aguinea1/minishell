/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:29:58 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/03 18:21:29 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void    ft_swap_lst(t_env *a, t_env *b)
{
    char *temp_key = a->key;
    char *temp_value = a->value;

    a->key = b->key;
    a->value = b->value;
    b->key = temp_key;
    b->value = temp_value;
}

int ft_strcmp(const char *s1, const char *s2)
{
    unsigned char c1, c2;

    while (*s1 && *s2)
    {
        c1 = (unsigned char)*s1;
        c2 = (unsigned char)*s2;
        if (c1 != c2)
            return (c1 - c2);

        s1++;
        s2++;
    }
    return ((unsigned char)*s1 - (unsigned char)*s2);
}

static void	ft_bubble(t_env *export)
{
	t_env	*tmp;
	t_env	*before;

	before = export;
	tmp = export->next;
	while (tmp)
	{
		if (ft_strcmp(before->key, tmp->key) > 0)
		{
			ft_swap_lst(before, tmp);
			before = export;
			tmp = export->next;
		}
		else
		{
			tmp = tmp->next;
			before = before->next;
		}
	}
}
/*
static void	ft_export_lonely(t_env *export)
{
	t_env	*tmp;

	tmp = export;
	if (!export)
		return ;
	ft_bubble(export);
	while (tmp)
	{
		if (tmp->value[0])
			ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else if (tmp->value)
			ft_printf("declare -x %s=\"\"\n", tmp->key);
		else
			ft_printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}

}*/

static void	ft_export_lonely(t_env *export)
{
	t_env	*tmp;

	tmp = export;
	if (!export)
		return ;
	ft_bubble(export);
	while (tmp)
	{
		if (tmp->value)
		{		
			if (tmp->value == NULL)
				ft_printf("declare -x %s\n", tmp->key);
			else 
				ft_printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		}
		else
		{
			ft_printf("declare -x %s\n", tmp->key);
		}
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

int	mini_export(t_command *cmd, t_env *export, int flag)
{
    t_env   *tmp;
    int     value_start;
    t_env   *new_node;
    char    *is_equal;
    char    *temp_value;
    char    *arg;

    if (!export || !cmd || !cmd->args || !cmd->args[1])
    {
        if (flag == 1)
            ft_export_lonely(export);
        return(1);
    }
    
    arg = cmd->args[1];
    tmp = export;
    value_start = find_key(arg);
    is_equal = arg;
    
    while (tmp)
    {
        if (ft_strncmp(tmp->key, arg, value_start - 1) == 0)
        {
            temp_value = ft_strdup(arg + value_start);
            if (!temp_value)
                return (1);
            free(tmp->value);
            tmp->value = temp_value;
            return (0);
        }
        tmp = tmp->next;
    }

    new_node = malloc(sizeof(t_env));
    if (!new_node)
        return(0);
    temp_value = ft_strdup(arg + value_start);
    if (flag == 0 && is_equal[value_start - 1] != '=')
    {
        free(temp_value);
        free(new_node);
        return(0);
    }
    if (is_equal[value_start - 1] == '=')
    {
        if (temp_value[0] == '\0')
        {
            free(temp_value);
            temp_value = ft_strdup("");
        }
    }
    else
    {
        free(temp_value);
        temp_value = NULL;
    }
    new_node->key = ft_substr(arg, 0, value_start - 1);
    if (!new_node->key)
    {
        free(new_node);
        free(temp_value);
        return(0);
    }
    new_node->value = temp_value;
    new_node->next = NULL;
    
    tmp = export;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
	return (1);
}
