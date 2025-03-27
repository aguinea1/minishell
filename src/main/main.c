/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/27 16:12:25 by isegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	free_spl(char **arg)
{
	int i = 0;
	while (arg[i])
	{
		free(arg[i]);
		arg[i] = NULL;
		i++;
	}
	free(arg);
}

static int	built_in(char *input, t_token *token, t_env *env_lst, t_env *export)
{
	char	**args;

	args = ft_split(input, ' ');
	if (ft_strcmp(args[0], "pwd") == 0)
		return (free_spl(args),pwd(), 0);
	if (ft_strcmp(args[0], "cd") == 0)
		return (cd(args, env_lst), free_spl(args), 0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (echo(args), free_spl(args), 0);
	if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env_lst), free_spl(args), 0);
	if (ft_strcmp(args[0], "export") == 0)
	{
		ft_export(token, export, 1);
		ft_export(token, env_lst, 0);
		return (free_spl(args), 0);
	}
	if (ft_strcmp(args[0], "unset") == 0)
		return (free_spl(args), ft_unset(token, env_lst, export), 0);
	return (free_spl(args), 1);
}

void	minishell_loop(t_env *env, t_env *export)
{
	char		*input;
	t_token		*token;
	t_command	*command;
	t_shell		*shell;
	int	exit_status;

	exit_status = 1;
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
		token = tokenizer(input);
		ft_expansor(token, env, exit_status);
		if (built_in(input, token, env, export) == 0)
		{
			free(input);
			free_tokens(&token);
			continue ;
		}
		if (syntax_analize(token) == 0)
		{
			command = parse_pipeline(token);
			shell = setup_exec(command);
			exit_status = exec_cmd(command, shell, env);
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
			free_env(&export);
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
	t_env	*export;

	(void)ac;
	(void)av;
	env_lst = init_env(env);
	export = init_env(env);
	minishell_loop(env_lst, export);
	return (0);
}
