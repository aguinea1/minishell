/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:18:40 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/03 18:19:24 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	check_child_builtin(t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		exit(mini_pwd());
	else if (ft_strcmp(cmd->args[0], "echo") == 0)
		exit(mini_echo(cmd->args));
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		exit(mini_env(*env));
}

int	check_parent_builtin(t_command *cmd, t_shell *shell,
	t_env **env, t_env **exp)
{
	if (!cmd->args)
		return (0);
	if (ft_strcmp(cmd->args[0], "cd") == 0)
	{
		shell->builtins_exit_status = mini_cd(cmd->args, *env, shell->n_cmds);
		return (1);
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
	{
		shell->builtins_exit_status = mini_unset(cmd, env, exp, shell->n_cmds);
		return (1);
	}
	if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		shell->builtins_exit_status = mini_export(cmd, *exp, 1);
		shell->builtins_exit_status = mini_export(cmd, *env, 0);
		return (1);
	}
	return (0);
}
