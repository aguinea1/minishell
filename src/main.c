/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcebria <arcebria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:47:19 by arcebria          #+#    #+#             */
/*   Updated: 2025/03/26 11:56:14 by aguinea          ###   ########.fr       */
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
		return (free_spl(args), ft_export(token, env_lst), ft_export(token, export), 0);
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
	t_heredoc	here;
	int			exit_status;

	command = NULL;
	here.num = 0;
	while (1)
	{
		input = readline("\033[1;34mminishell>\033[0m ");
		if (!input)
			break ;
		if (input[0])
			add_history(input);
		else
			continue ;
		token = tokenizer(input, &here);
		if (built_in(input, token, env, export) == 0)
		{
			free_tokens(&token);
			continue ;
		}
		if (here.num > 0)
		{
			here_loop(&here, token);
			here.num = 0;
		}
		if (syntax_analize(token) == 0)
		{
			command = parse_pipeline(token);
			shell = setup_exec(command);
			exit_status = exec_cmd(command, shell, env);
		}
		(void)exit_status;
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
		unlink("/tmp/heredoc_tmp");
	}
	rl_clear_history();
	unlink("/tmp/heredoc_tmp");
	free_env(&env);
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
