#include "../inc/minishell.h"

void	unset_envp(t_shell *shell, char *unset)
{
	t_envp	*tmp;
	t_envp	*tmp2;
	t_envp	*tmp3;
	int	i;

	tmp = shell->envp;
	i = 0;
	if (!ft_strncmp(tmp->var, unset, ft_strlen(tmp->var)))
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2->var);
		free(tmp2->values);
		free(tmp2);
	}
	else
	{
		tmp3 = tmp;
		while (tmp3->next != NULL)
		{
			if (!ft_strncmp(tmp3->next->var, unset, ft_strlen(tmp3->next->var)))
			{
				tmp2 = tmp3->next;
				tmp3->next = tmp3->next->next;
				free(tmp2->var);
				free(tmp2->values);
				free(tmp2);
				break ;
			}
			else
				tmp3 = tmp3->next;
		}
	}

}
