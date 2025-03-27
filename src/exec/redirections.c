//header

//problemas cuando se redirecciona a dos outputs diferentes ls > out > out2

#include "../inc/minishell.h"

int	set_input_redir(t_shell *shell, int fd, int type)
{
	if (type == 0)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (1);
		close(fd);
		shell->flag_in = 1;
	}
	return (0);
}

int	set_output_redir(t_shell *shell, int fd, int type)
{
	if (type == 0)
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
		close(fd);
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
			return (1);
		close(fd);
		shell->flag_out = 1;
	}
	return (0);
}


int	redir_first_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if ((tmp->type == REDIR_IN || tmp->type == HEREDOC) && set_input_redir(shell, tmp->fd_in, 0))
			return (1);
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND))
		{
			if (set_output_redir(shell, tmp->fd_out, 0))
				return (1);
		}
		else
		{
			if (set_output_redir(shell, shell->pipes[1], 0))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir_last_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if ((tmp->type == REDIR_IN || tmp->type == HEREDOC) && set_input_redir(shell, tmp->fd_in, 1))
			return (1);
		else if ((tmp->type != REDIR_IN || tmp->type == HEREDOC) && shell->flag_in == 0)
		{
			if (set_input_redir(shell, shell->pipes[2 * shell->child - 2], 1))
				return (1);
		}
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND) && set_output_redir(shell, tmp->fd_out, 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	redir_n_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if ((tmp->type == REDIR_IN || tmp->type == HEREDOC) && set_input_redir(shell, tmp->fd_in, 1))
			return (1);
		else if ((tmp->type != REDIR_IN || tmp->type == HEREDOC) && shell->flag_in == 0
				&& set_input_redir(shell, shell->pipes[2 * shell->child - 2], 0))
			return (1);
		if ((tmp->type == REDIR_OUT || tmp->type == APPEND)
				&& set_output_redir(shell, tmp->fd_out, 1))
			return (1);
		else if (tmp->type != REDIR_OUT && tmp->type != APPEND && shell->flag_out == 0
				&& set_output_redir(shell, shell->pipes[2 * shell->child + 1], 0))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
