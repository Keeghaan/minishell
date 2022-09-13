#include "../inc/minishell.h"

char	*get_var(char *argv)
{
	int	i;
	char	*var;

	i = 0;
	while (argv[i] != '=')
		i++;
	var = ft_substr(argv, 0, i);
	return (var);
}

char	*get_values(char *argv)
{
	int	i;
	int	j;
	char	*values;

	i = 0;
	j = 0;
	while (argv[i] != '=')
		i++;
	i++;
	values = ft_substr(argv, i, ft_strlen(argv));
	return (values);
}

void	add_exported(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	tmp = *envp;
	printf("%s\n", tmp->var);
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	tmp->next = new;
	printf("%s\n", tmp->next->var);
}

t_envp	*make_exported(char *argv)
{
	t_envp	*new;
	char	*var;
	char	*values;
	
	var = get_var(argv);
	values = get_values(argv);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->var = ft_strdup(var);
	if (!new->var)
		return (free(new), NULL);
	new->values = ft_strdup(values);
	if (!new->values)
		return (free(new->var), free(new), NULL);
	new->next = NULL;
	free(var);
	free(values);
	return (new);
}

/*t_envp	*add_exported(t_envp **env, char *var, char *values)
{
	t_envp	*new;
	
	new = malloc(sizeof(env));
	if (!new)
		return (NULL);
	new->var = ft_strdup(var);
	if (!new->var)
		return (free(new), NULL);
	new->values = ft_strdup(values);
	if (!new->values)
		return (free(new->var), free(new), NULL);
	new->next = NULL;
	return (new);
}*/

void	check_export(char *opt_var, t_shell *shell) //var ou autre ?
{
	int	exported;

	exported = 0;
	while (shell->envp)
	{
		if (!ft_strncmp(opt_var, shell->envp->var, ft_strlen(opt_var)))
		{
			shell->envp->exported = 1;
			exported = 1;
			printf("check export %s (%s)\n", shell->envp->var, shell->envp->values);
		}
		if (shell->envp->next)
			shell->envp = shell->envp->next;
		else
			break ;
	}
//	if (!exported)
//		printf("Not exported\n");
}

void	export_var(t_shell *shell, t_envp *envp)
{
	t_envp	*new;

	if (shell->cmds->full_cmd[1] && !ft_strchr(shell->cmds->full_cmd[1], '='))
		check_export(shell->cmds->full_cmd[1], shell);
	else if (!shell->cmds->full_cmd[1])
	{
		while (shell->envp)
		{
			printf("export %s=\"%s\"\n", shell->envp->var, shell->envp->values); //declare -x ou export ?
			shell->envp->exported = 1;
			if (shell->envp->next)
				shell->envp = shell->envp->next;
			else
				break ;
		}
	}
	else if (ft_strchr(shell->cmds->full_cmd[1], '='))
	{
		new = make_exported(shell->cmds->full_cmd[1]);
		add_exported(&envp, new);
	}
}
