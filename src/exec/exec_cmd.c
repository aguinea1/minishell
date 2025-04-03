/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:40 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/03 18:12:49 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	cmd_size(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	tmp = cmd;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	exe_child(t_command *cmd, t_shell *shell, t_env *env)
{
	if (!cmd->args)
	{
		if (search_heredoc(cmd->redirs))
			exit(0);
		else
			exit(127);
	}
	if (set_dup(cmd->redirs, shell) == 1)
		exit(1);
	close_pipes(shell);
	check_child_builtin(cmd, &env);
	execve(cmd->path, cmd->args, cmd->env_array);
	err_out("minishell: ", "command not found: ", "", cmd->args[0]);
	exit(127);
}

int	exe_parent(t_command *cmd, t_shell *shell)
{
	int		exit_status;
	int		status;
	pid_t	wpid;

	exit_status = shell->builtins_exit_status;
	shell->child--;
	close_fds(cmd, shell);
	while (shell->child >= 0)
	{
		wpid = waitpid(shell->pids[shell->child], &status, 0);
		if (wpid == shell->pids[shell->n_pipes])
		{
			if (shell->child == (shell->n_pipes) && WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
		}
		shell->child--;
	}
	free(shell->pipes);
	free(shell->pids);
	make_unlink(cmd, shell);
	return (exit_status);
}

int	exec_cmd(t_command *cmd, t_shell *shell, t_env *env, t_env *export)
{
	t_command	*c_tmp;

	c_tmp = cmd;
	setup_signals(0);
	while (shell->child < shell->n_cmds)
	{
		if (check_parent_builtin(c_tmp, shell, &env, &export))
		{
			shell->child++;
			c_tmp = c_tmp->next;
			continue ;
		}
		get_cmd(c_tmp, env);
		shell->pids[shell->child] = fork();
		if (shell->pids[shell->child] == -1)
			return (perror("fork"), 1);
		else if (shell->pids[shell->child] == 0)
			exe_child(c_tmp, shell, env);
		shell->child++;
		c_tmp = c_tmp->next;
	}
	return (exe_parent(cmd, shell));
}
