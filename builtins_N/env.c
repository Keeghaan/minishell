#include "../inc/minishell.h"

void	display_environment(t_shell *shell)
{
	t_envp	*tmp;

	tmp = shell->envp;
	while (tmp)
	{
		ft_putstr_fd(tmp->var, 1);
		write(1, "=", 1);
		ft_putendl_fd(tmp->values, 1);
		tmp = tmp->next;
	}
}
