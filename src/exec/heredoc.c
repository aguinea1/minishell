/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:51:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/26 15:29:47 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int here_loop(t_heredoc *doc, t_token *token)
{
    char    *line;
    int     heredoc_fd;
    t_token *head;
    char    *content;
    int     len;

    head = token;
    len = 0;
    content = NULL;

    // Crear el archivo heredoc
    heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (heredoc_fd == -1)
    {
        perror("open");
        return (-1);
    }

    // Avanzar hasta el token HEREDOC
    while (token && token->type != HEREDOC)
        token = token->next;

    // Si no hay token HEREDOC o el siguiente token es nulo
    if (!token || !token->next)
    {
        close(heredoc_fd);
        return (-1);
    }

    // Mover al siguiente token después de HEREDOC
    token = token->next;

    // Leer las líneas del heredoc
    while (doc->num > 0)
    {
        line = readline("\033[1;37mheredoc>\033[0m ");
        if (!line) // Si la línea está vacía, salir
            break;

        // Compara la línea con el delimitador del heredoc
        if (token && token->type == WORD && ft_strcmp(token->value, line) == 0)
        {
            doc->num--;
            if (doc->num == 0)
            {
                free(line);
                break;
            }
            token = token->next;
            if (token->next && token->next->type == WORD)
                token = token->next;
        }
        else if (head->type != WORD) // Si no es un token WORD
        {
            if (content == NULL)
                content = ft_strjoin(line, "\n");
            else
            {
                content = ft_strjoin(content, line);
                content = ft_strjoin(content, "\n");
            }
            len += ft_strlen(line) + 1; // Acumular el tamaño de la línea
        }
        else
        {
            // Escribir en el archivo heredoc
            write(heredoc_fd, line, ft_strlen(line));
            write(heredoc_fd, "\n", 1);
        }

        free(line); // Liberar la memoria de la línea
    }

    // Si hay contenido acumulado, escribirlo en la salida estándar
    if (content != NULL)
        write(1, content, len);

    close(heredoc_fd); // Cerrar el archivo heredoc
    return (0);
}

/*
int here_loop(t_heredoc *doc, t_token *token)
{
    char    *line;
    int     heredoc_fd;
	t_token	*head;
	char	*content;
	int len;

	head = token;
	len = 0;
	content = NULL;
    heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (heredoc_fd == -1)
    {
        perror("open");
        return (-1);
    }
	while (token)
	{
		if (token->type == HEREDOC)
			break;
		token = token->next;
	}	
    if (!token || !token->next)
    {
        close(heredoc_fd);
        return (-1);
    }

    token = token->next;

    while (doc->num > 0)
    {
        line = readline("\033[1;37mheredoc>\033[0m ");
        if (!line)
            break;
		if (token && token->type == WORD && ft_strcmp(token->value, line) == 0)
		{
			doc->num--;
			if (doc->num == 0)
			{
				free(line);
				break;
			}
			token = token->next;
			while (token && token->type != HEREDOC)
				token = token->next;
		}
		else if (head->type != WORD)
		{
			if (content == NULL)
				content = ft_strjoin(line, "\n");
			else
			{
				content = ft_strjoin(content, line);
				content = ft_strjoin(content, "\n");
			}
			len += ft_strlen(line) + 1;
		}
        else
        {
            write(heredoc_fd, line, ft_strlen(line));
            write(heredoc_fd, "\n", 1);
        }
        free(line);
    }
	if (content != NULL)
		write(1, content, len);
    close(heredoc_fd);
    return (0);
}*/
