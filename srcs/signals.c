/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:25:11 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/23 15:19:01 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigquit_chld(int sig)
{
	(void)sig;
	ft_putendl_fd("Quit (Core dumped)", 1);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_chld(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	signalisation(int child)
{
	/*struct sigaction	si;
	struct sigaction	sq;

	ft_memset(&si, 0, sizeof(si));
	ft_memset(&sq, 0, sizeof(sq));
	if (child)
	{
		si.sa_handler = &handle_sigint_chld;
		sq.sa_handler = &handle_sigquit_chld;
	}
	else
	{
		si.sa_handler = &handle_sigint;
		sq.sa_handler = SIG_IGN;
	}
	si.sa_flags = SA_RESTART;
	sq.sa_flags = SA_RESTART;
	sigaction(SIGINT, &si, NULL);
	sigaction(SIGQUIT, &sq, NULL);
}

void	handle_mister_here(int sig)
{
	(void)sig;
	g_return = 130;
	if (STDIN_FILENO != -1)
		close(STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	sigaction(SIGQUIT, &sq, NULL);*/
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}
