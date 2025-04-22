/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <aguinea@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 21:07:16 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/22 12:45:33 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern volatile sig_atomic_t	g_sigint;

int	handle_exit(char *input, t_command **cmd, t_env **env, int *status)
{
	char	**args;
	int		code;

	args = ft_split(input, ' ');
	if (!args || !args[0])
		return (ft_free_array(args), 2);
	if (ft_strncmp(args[0], "exit", 5) != 0)
		return (ft_free_array(args), 2);
	write(1, "exit\n", 5);
	if (!args[1])
		return (ft_free_array(args), free(input), 0);
	if (!ft_issigneddigit(args[1]))
		return (write(2, "minishell: exit: numeric argument required\n", 43),
			ft_free_array(args), free(input), *status = 2, 0);
	if (args[2])
		return (write(2, "minishell: exit: too many arguments\n", 36),
			ft_free_array(args), free(input), *status = 1, 1);
	code = ft_atoi(args[1]);
	ft_free_array(args);
	free_commands(cmd);
	free_env(env);
	free(input);
	*status = code;
	return (0);
}

int	handle_input(char **input, t_command **command, t_env **env, int *status)
{
	int	exit_code;

	*input = readline("\033[1;34mminishell>\033[0m ");
	if (!*input)
	{
		ft_putendl_fd("exit", 1);
		return (0);
	}
	if ((*input)[0])
		add_history(*input);
	else
	{
		free(*input);
		return (1);
	}
	exit_code = handle_exit(*input, command, env, status);
	if (exit_code != 2)
		return (exit_code);
	return (2);
}

int	process_token(char *input, t_env *env,
			int *exit_status, t_token **token)
{
	*token = tokenizer(input, env, *exit_status);
	if (*token == NULL)
	{
		if (input)
			free(input);
		*exit_status = 1;
		return (1);
	}
	if (syntax_analize(*token) != 0)
	{
		if (input)
			free(input);
		*exit_status = 2;
		free_tokens(token);
		return (1);
	}
	return (0);
}

void	execute_command(t_token *token, t_env **env,
			t_env **export, int *exit_status)
{
	t_command	*command;
	t_shell		*shell;

	command = parse_pipeline(token);
	shell = setup_exec(command, *exit_status, *env);
	*exit_status = exec_cmd(command, shell, env, export);
	setup_signals(1);
	free_tokens(&token);
	free_commands(&command);
	free(shell);
}

int	minishell_loop(t_env *env, t_env *export)
{
	char		*input;
	t_token		*token;
	int			exit_status;
	int			status;

	exit_status = 0;
	setup_signals(1);
	while (1)
	{
		status = handle_input(&input, NULL, &env, &exit_status);
		if (g_sigint == 1)
		{
			exit_status = 130;
			g_sigint = 0;
		}
		if (status == 0)
			break ;
		if (status == 1)
			continue ;
		if (process_token(input, env, &exit_status, &token) != 0)
			continue ;
		execute_command(token, &env, &export, &exit_status);
		free(input);
	}
	return (free_env(&env), rl_clear_history(), free_env(&export), exit_status);
}
