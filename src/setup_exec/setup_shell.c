/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:26:05 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/02 16:34:50 by arcebria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	create_pipes(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->n_pipes * 2)
	{
		if (pipe(shell->pipes + (2 * i)) == -1)
			perror("pipe");
		i++;
	}
}

t_shell	*init_shell(t_command *cmd)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->child = 0;
	shell->n_cmds = cmd_size(cmd);
	shell->n_pipes = shell->n_cmds - 1;
	shell->flag_in = 0;
	shell->flag_out = 0;
	shell->here_doc = 0;
	shell->hd_count = 0;
	shell->builtins_exit_status = 1;
	shell->pids = malloc(sizeof(pid_t) * shell->n_cmds);
	if (!shell->pids)
		return (NULL);
	shell->pipes = malloc(sizeof(int *) * shell->n_pipes * 2);
	if (!shell->pipes)
		return (NULL);
	return (shell);
}
