/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:27:40 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/26 18:31:17 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void close_pipes(t_shell *shell)
{
    int i = 0;
    while (i < shell->n_pipes * 2)
    {
        close(shell->pipes[i]);
        i++;
    }
}

void close_fds(t_command *cmd, t_shell *shell)
{
    t_command *c_tmp = cmd;
    t_redirection *r_tmp;

    while (c_tmp)
    {
        r_tmp = c_tmp->redirs;
        while (r_tmp)
        {
            if (r_tmp->fd_in >= 0)
                close(r_tmp->fd_in);
            if (r_tmp->fd_out >= 0)
                close(r_tmp->fd_out);
            r_tmp = r_tmp->next;
        }
        c_tmp = c_tmp->next;
    }
    close_pipes(shell);
}

int cmd_size(t_command *cmd)
{
    int i = 0;
    while (cmd)
    {
        i++;
        cmd = cmd->next;
    }
    return i;
}

int redir_one_cmd(t_redirection *redir)
{
    while (redir)
    {
        if (redir->type == REDIR_IN)
        {
            if (dup2(redir->fd_in, STDIN_FILENO) == -1)
                return perror("dup2 in"), 1;
            close(redir->fd_in);
        }
        else if (redir->type == REDIR_OUT || redir->type == APPEND)
        {
            if (dup2(redir->fd_out, STDOUT_FILENO) == -1)
                return perror("dup2 out"), 1;
            close(redir->fd_out);
        }
        redir = redir->next;
    }
    return 0;
}
/*
int redir_pipes(t_redirection *redir, t_shell *shell)
{
    if (shell->child == 0)
    {
        if (!redir && dup2(shell->pipes[1], STDOUT_FILENO) == -1)
            return perror("dup2 first child out"), 1;
    }
    else if (shell->child == shell->n_pipes)
    {
        if (!redir && dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
            return perror("dup2 last child in"), 1;
    }
    else
    {
        if (!redir)
        {
            if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
                return perror("dup2 mid child in"), 1;
            if (dup2(shell->pipes[2 * shell->child + 1], STDOUT_FILENO) == -1)
                return perror("dup2 mid child out"), 1;
        }
    }
	close_pipes(shell);
    return 0;
}
*/
int redir_pipes(t_redirection *redir, t_shell *shell)
{
    if (shell->child == 0) // Primer proceso
    {
        if (redir_one_cmd(redir) == 0) // Si no hay error en redirecciones
        {
            if (dup2(shell->pipes[1], STDOUT_FILENO) == -1)
                return perror("dup2 first child out"), 1;
        }
    }
    else if (shell->child == shell->n_pipes) // Último proceso
    {
        if (redir_one_cmd(redir) == 0)
        {
            if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
                return perror("dup2 last child in"), 1;
        }
    }
    else // Proceso intermedio
    {
        if (redir_one_cmd(redir) == 0)
        {
            if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
                return perror("dup2 mid child in"), 1;
            if (dup2(shell->pipes[2 * shell->child + 1], STDOUT_FILENO) == -1)
                return perror("dup2 mid child out"), 1;
        }
    }

    close_pipes(shell);
    return 0;
}

int dup_files(t_redirection *redir, t_shell *shell)
{
    if (shell->n_cmds == 1)
        return redir_one_cmd(redir);
    return redir_pipes(redir, shell);
}

void exe_child(t_command *cmd, t_shell *shell)
{
    if (dup_files(cmd->redirs, shell))
        exit(1);
    int heredoc_fd = open("/tmp/heredoc_tmp", O_RDONLY);
    if (heredoc_fd != -1)
    {
        if (dup2(heredoc_fd, STDIN_FILENO) == -1)
        {
            perror("dup2 heredoc");
            close(heredoc_fd);
            exit(1);
        }
        close(heredoc_fd);
    }
    close_pipes(shell);
    if (cmd->args && cmd->args[0])
    {
        execve(cmd->path, cmd->args, cmd->env_array);
        perror("execve failed");
        exit(127);
    }
    exit(0);
}

void clean_fds(t_command *cmd)
{
    t_command *c_tmp = cmd;
    t_redirection *r_tmp;
    while (c_tmp)
    {
        r_tmp = c_tmp->redirs;
        while (r_tmp)
        {
            if (r_tmp->fd_in >= 0)
                close(r_tmp->fd_in);
            if (r_tmp->fd_out >= 0)
                close(r_tmp->fd_out);
            r_tmp = r_tmp->next;
        }
        c_tmp = c_tmp->next;
    }
}

int exe_parent(t_command *cmd, t_shell *shell)
{
    int status;
    shell->child--;
    close_fds(cmd, shell);
    clean_fds(cmd);
    while (shell->child >= 0)
    {
       if( waitpid(shell->pids[shell->child], &status, 0) == -1)
		   perror ("waitpid");
        shell->child--;
    }
    free(shell->pipes);
    free(shell->pids);
    return (WIFEXITED(status)) ? WEXITSTATUS(status) : 1;
}

int exec_cmd(t_command *cmd, t_shell *shell, t_env *env)
{
	setup_signals(0);
    if (!cmd || !cmd->args)
        return 127;
    while (shell->child < shell->n_cmds)
    {
        get_cmd(cmd, env);
        shell->pids[shell->child] = fork();
        if (shell->pids[shell->child] == -1)
            return perror("fork"), 1;
        else if (shell->pids[shell->child] == 0)
            exe_child(cmd, shell);
        shell->child++;
        cmd = cmd->next;
    }
    return exe_parent(cmd, shell);
}
