#include "../inc/minishell.h"

t_envp	*add_exported(t_envp **env, char *var, char *values)
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
}
/*
void	get_exported_data(t_shell *shell, int i, int j)
{
	t_envp	*tmp;
	char	*var;
	char	*values;

	j = 0;
	while (new_var[j] != '=')
		j++;
	var = ft_substr(new_var, 0, j - 1);
	values = ft_substr(new_var, j + 1, ft_strlen(new_var) - j);
	tmp = shell->envp;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = add_exported(shell->envp, var, values);
	free(var);
	free(values);
}

void	export_variable(t_shell *shell, char **new_var)
{
	t_envp	*tmp;
	char	*var;
	char	*values;
	int	i;
	int	j;

	i = 0;
	while (new_var[i])
	{
		if ((ft_isdigit(new_var[i][0]) || !ft_isalpha(new_var[i])) && new_var[i] != '_')
		{
			ft_printf("minishell: export: `%s': not a valid identifier", new_var[i]);
		}
		if (ft_strchr(new_var[i], '='))
			get_exported_data(shell, i, j);
		i++;
	}
}
*/
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
	if (!exported)
		printf("Not exported\n");
}

void	export_var(t_shell *shell, t_envp *envp)
{
(void)envp; //on en aura besoin en cas d'option (export PATH, ou autre)
//	if (shell->cmds->full_cmd[1])
//		check_export(shell->cmds->full_cmd[1], shell);
//	else
//	{
		while (shell->envp)
		{
			printf("export %s=\"%s\"\n", shell->envp->var, shell->envp->values); //declare -x ou export ?
			shell->envp->exported = 1;
			if (shell->envp->next)
				shell->envp = shell->envp->next;
			else
				break ;
		}
//	}
}
