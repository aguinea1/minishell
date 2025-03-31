/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:58 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/31 20:28:12 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

# define S_E_PIPE "minishell: syntax error near unexpected token `|'\n"
# define S_E_REDIR "minishell: syntax error near unexpected token `newline'\n"

typedef enum s_token_type
{
	WORD, // TEXTO
	PIPE, // |
	REDIR_IN, // <
	REDIR_OUT, // >
	HEREDOC, // <<
	APPEND, // >>
	AMPERSAND, // &
	OR // ||
}	t_token_type;

typedef struct s_shell
{
	int		n_pipes;
	int		n_cmds;
	int		*pipes;
	pid_t	*pids;
	int		child;
	int		flag_in;
	int		flag_out;
	int		here_doc;
}	t_shell;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_redirection
{
	int						type;
	char					*file;
	int						fd_in;
	int						fd_out;
	char					*hd_filename;
	struct s_redirection	*next;
}	t_redirection;

typedef struct s_command
{
	char				**args;
	char				**env_array;
	char				*path;
	t_redirection		*redirs;
	struct s_command	*next;
}	t_command;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

t_token		*tokenizer(char *input, t_env *env, int exit_status);
void		free_tokens(t_token **token);
t_command	*parse_pipeline(t_token	*token);
int			syntax_analize(t_token *tokens);
void		free_commands(t_command	**cmds);
void		free_tokens(t_token **token);
void		free_env(t_env **env);
void		get_cmd(t_command *cmd, t_env *env);
//void	echo(char **args);
//void	cd(char **args, t_env *env_lst);
//void	pwd(void);
t_env		*init_env(char **env);
int			exec_cmd(t_command *cmd, t_shell *shell, t_env *env);
t_shell		*setup_exec(t_command *cmd);
int			cmd_size(t_command *cmd);
int			redir_first_child(t_redirection *redir, t_shell *shell);
int			redir_last_child(t_redirection *redir, t_shell *shell);
int			redir_n_child(t_redirection *redir, t_shell *shell);
void		err_out(char *str1, char *str2, char *str3, char *str4);
void	ft_export(t_token *token, t_env *env_lst, int flag);
void	ft_unset(t_token *token, t_env *env_lst, t_env *export);
void	pwd(void);
void	cd_home(char *home);
void	cd_oldpwd(char *oldpwd);
void	update_env(t_env *env_lst, char *key, char *new_value);
char	*get_oldpwd(t_env *env);
void	cd(char **args, t_env *env_lst, t_token *token);
void	echo(char **args, t_token *token);
void	ft_env(t_env *env_lst);
void	sigint_handler(int signum);
void	setup_signals(int signal);
t_command	*init_command(void);
void	add_redir_utils(t_redirection *tmp,t_command *cmd, t_redirection *redir);
void	ft_expansor(t_token *token, t_env *env, int exit_status);

#endif
