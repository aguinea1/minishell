/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:51:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/03/24 16:51:21 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
    while (token && token->type != HEREDOC)
        token = token->next;

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
			if (token->next->type == WORD)
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
}

