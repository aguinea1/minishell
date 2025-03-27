//header

#include "../inc/minishell.h"


int redir_first_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
				exit(1); //implementar dentro de las redirecciones de los hijos que si hay algun dup que falla salga, hacer una funcion para gestionar todos los exits
			close(tmp->fd_in);
		}
		if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
				return (1);
			close(tmp->fd_out);
		}
		else
		{
			if (dup2(shell->pipes[1], STDOUT_FILENO) == -1)
				return (1);
		
		}
		tmp = tmp->next;
	}
	return (0);
}

int	redir_last_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;
	int				flag;

	tmp = redir;
	flag = 0;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
				return (1);
			close(tmp->fd_in);
			flag = 1;
		}
		else if (tmp->type != REDIR_IN && flag == 0)
		{
			if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
				return (1);
			flag = 1;
		}
		if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
				return (1);
			close (tmp->fd_out);
		}
		tmp = tmp->next;
	}
	return (0);	
}

int	redir_n_child(t_redirection *redir, t_shell *shell)
{
	t_redirection	*tmp;
	int				flag_in;
	int				flag_out;

	tmp = redir;
	flag_in = 0;
	flag_out = 0;
	while (tmp)
	{
		if (tmp->type == REDIR_IN)
		{
			if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
				return (1);
			close (tmp->fd_in);
			flag_in = 1;
		}
		else if (tmp->type != REDIR_IN && flag_in == 0)
		{
			if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
				return (1);
		}
		if (tmp->type == REDIR_OUT || tmp->type == APPEND)
		{
			if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
				return (1);
			close (tmp->fd_out);
			flag_out = 1;
		}
		else if (tmp->type != REDIR_OUT && tmp->type != APPEND && flag_out == 0)
		{
			if (dup2(shell->pipes[2 * shell->child + 1], STDOUT_FILENO) == -1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}















































/*int	redir_pipes(t_redirection *redir, t_shell *shell)
{
	t_redirection *tmp;

	tmp = redir;
	if (shell->child == 0)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_IN)
			{
				if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
					return (1);
				close(tmp->fd_in);
				printf("Primer nodo -- File: %s fd_in: %d\n", tmp->file, tmp->fd_in);
			}
			if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			{
				printf("Primer nodo -- File: %s fd_out: %d\n", tmp->file, tmp->fd_out);
				if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
					return (1);
				close(tmp->fd_out);
			}
			else
			{
				printf("CACA -- File: %s fd_out: %d\n", tmp->file, tmp->fd_out);
				if (dup2(shell->pipes[1], STDOUT_FILENO) == -1)
					return (1);
			}
			tmp = tmp->next;
		}
	}
	else if (shell->child == shell->n_pipes)
	{
		while (tmp)
		{
			if (tmp->type == REDIR_IN)
			{
				printf("Segundo nodo -- File: %s fd_in: %d\n", tmp->file, tmp->fd_in);
				if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
					return (1);
				close(tmp->fd_in);
			}
			else
			{
				if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
					return (1);
			}
			if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			{
				printf("Segundo nodo -- File: %s fd_out: %d\n", tmp->file, tmp->fd_out);
				if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
					return (1);
				close (tmp->fd_out);
			}
			tmp = tmp->next;
		}
	}
	else
	{
		while (tmp)
		{
			if (tmp->type == REDIR_IN)
			{
				if (dup2(tmp->fd_in, STDIN_FILENO) == -1)
					return (1);
				close (tmp->fd_in);
			}
			else
			{
				if (dup2(shell->pipes[2 * shell->child - 2], STDIN_FILENO) == -1)
					return (1);
			}
			if (tmp->type == REDIR_OUT || tmp->type == APPEND)
			{
				if (dup2(tmp->fd_out, STDOUT_FILENO) == -1)
					return (1);
				close (tmp->fd_out);
			}
			else
			{
				if (dup2(shell->pipes[2 * shell->child + 1], STDOUT_FILENO) == -1)
					return (1);
			}
			tmp = tmp->next;
		}
	}
	return (0);
}*/