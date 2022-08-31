//PAS UTILE ??

#include "../inc/minishell.h"

void	display_pwd(t_shell *shell)
{
	t_shell	tmp;
	char	*pwd;

	tmp = shell;
	while (tmp->envp)
	{
		if (!ft_strncmp(shell->envp->var, "PWD", ft_strlen(shell->envp->var)))
		{
			ft_putendl_fd(shell->envp->values, 1);
			break ;
		}
		tmp->envp = tmp->envp->next;
	}
}
