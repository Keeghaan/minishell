#include "../inc/minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signalisation(void)
{
	struct sigaction	si;
	struct sigaction	sq;

	ft_memset(&si, 0, sizeof(si));
	ft_memset(&sq, 0, sizeof(sq));
	si.sa_handler = &handle_sigint;
	sq.sa_handler = SIG_IGN;
	si.sa_flags = SA_RESTART;
	sq.sa_flags = SA_RESTART;
	sigaction(SIGINT, &si, NULL);
	sigaction(SIGQUIT, &sq, NULL);
	
}
