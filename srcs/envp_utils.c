#include "../inc/minishell.h"

t_envp	*make_new_env(char *envp)
{
	t_envp	*new;
	char	*line;
	int		i;
	int		j;

	i = 0;
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	while (envp[i] != '=')
		i++;
	new->var = ft_substr(envp, 0, i);
	j = i + 1;
	while (envp[j] != '\n' && envp[j] != '\0')
		j++;
	line = ft_substr(envp, i + 1, j - 1);
	new->values = ft_strdup(line);
	new->next = NULL;
	free(line);
	return (new);
}

void	add_new_env(t_envp **env, char *envp)
{
	t_envp	*tmp;

	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = make_new_env(envp);
}

void	envp_to_lst(t_envp **env, char **envp)
{
	int	i;

	i = 0;
	if (!envp[0])
	{
		*env = NULL;
		return ;
	}
	while (envp[i])
	{
		if (i == 0)
			*env = make_new_env(envp[i]);
		else
			add_new_env(env, envp[i]);
		i++;
	}
}

void	free_envp(t_envp **envp)
{
	t_envp	*tmp;
	t_envp	*alst;

	alst = *envp;
	while (alst)
	{
		tmp = alst;
		alst = alst->next;
		free(tmp->var);
		free(tmp->values);
		free(tmp);
	}
}

//cette fonction est faite pour le builtin unset, jamais testee
//https://www.log2base2.com/data-structured
///linked-list/deleting-a-node-in-linked-list.html

void	remove_env(t_envp **envp, char *var)
{
	t_envp	*tmp;
	t_envp	*tmp2;
	t_envp	*tmp3;

	tmp = *envp;
	if (!envp || !*envp || !var)
		return ;
	if (tmp->var == var)
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
