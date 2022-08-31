#include "../inc/minishell.c"

void	echo_stuff(t_shell *shell, char **stuff)
{
	int	i;

	i = 0;
	while (stuff[i])
	{
		ft_putendl_fd(stuff[i], 1);
		i++;	
	}
}
