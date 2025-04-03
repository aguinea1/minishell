/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/04/03 15:46:42 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	minishell_loop(t_env *env, t_env *export)
{
	char		*input;
	t_token		*token;
	t_command	*command;
	t_shell		*shell;
	int	exit_status;

	exit_status = 0;
	command = NULL;
	setup_signals(1);
	while (1)
	{
		input = readline("\033[1;34mminishell>\033[0m ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		else
		{
			free(input);
			continue ;
		}
		token = tokenizer(input, env, exit_status);
		if (token == NULL)
		{
			free(input);
			exit_status = 1;
			continue ;
		}
		if (syntax_analize(token) == 0)
		{
			command = parse_pipeline(token);
			shell = setup_exec(command, exit_status, env);
			exit_status = exec_cmd(command, shell, env, export);
			setup_signals(1);
		}
		else
		{
			free(input);
			free_tokens(&token);
			continue ;
		}
		if (ft_strcmp(input, "exit") == 0)
		{
			free_tokens(&token);
			free_commands(&command);
			free_env(&env);
			free(shell);
			free(input);
			break ;
		}
		free_tokens(&token);
		free_commands(&command);
		free(shell);
		free(input);
	}
	free_env(&env);
	rl_clear_history();
	free_env(&export);
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_lst;
	t_env	*exprt_lst;

	(void)ac;
	(void)av;
	if (!env | !*env)
	{
		env_lst = init_no_env(0);
		exprt_lst = init_no_env(1);
	}
	else
	{
		env_lst = init_env(env);
		exprt_lst = init_env(env);
	}
	minishell_loop(env_lst, exprt_lst);
	return (0);
}
