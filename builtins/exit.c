#include "../inc/minishell.h"

void	handle_exit(t_shell *shell, char *buf)
{
	char	**split;

	split = ft_split(buf, ' ');
	if (!split)
		return ;
	shell->is_running = 0;
	ft_putendl_fd("exit", 1);
	printf("minishell: %s: %s: numeric argument required\n", split[0], split[1]);
	free_split(split);
	exit(0);
}
