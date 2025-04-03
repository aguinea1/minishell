/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguinea <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:11:11 by aguinea           #+#    #+#             */
/*   Updated: 2025/04/03 18:11:16 by aguinea          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
static void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (signal == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

static void	child_handler(int signal)
{

	write(1, "\n", 1);
	if (signal == SIGQUIT)
	{
		write(1, "Quit: 3\n", 9);
	}
	return ;
}

void	setup_signals(int i)
{
	struct sigaction	sa;
	sigemptyset(&sa.sa_mask);

	if (i)
		sa.sa_handler = &signal_handler;
	else
	{
		sa.sa_handler = &child_handler;
	}
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGTERM, &sa, NULL);
}
