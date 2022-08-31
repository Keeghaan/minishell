#include "../inc/minishell.h"

void	unset_envp(t_shell *shell, char *unset)
{
	t_envp	*tmp;
	t_envp	*tmp2;
	t_envp	*tmp3;
	int	i;

	tmp = shell->envp;
	i = 0;
	if (tmp->var == unset)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	else
	{
		tmp3 = tmp;
		while (tmp3->next != NULL)
		{
			if (tmp3->next->var == var)
			{
				tmp2 = tmp3->next;
				tmp3->next = tmp3->next->next;
				free(tmp2);
				break ;
			}
			else
				tmp3 = tmp3->next;
		}
	}

}
