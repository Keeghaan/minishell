#include "../inc/minishell.h"

void	print_envp(t_envp *envp)
{
	t_envp	*tmp;

	tmp = envp;
	while (tmp)
	{
		printf("%s", tmp->var);
		printf("=");
		printf("%s\n", tmp->values);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}
