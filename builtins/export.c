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

char	*get_values(char *argv, t_shell *shell)
{
	int	i;
	int	j;
	char	*values;

	i = 0;
	j = 0;
	while (argv[i] != '=')
		i++;
	i++;
	if (!argv[i] && shell->token->next->next && (shell->token->next->next->quotes == 2 
		|| shell->token->next->next->quotes == 3))
		values = ft_strdup(shell->token->next->next->value);
	else
		values = ft_substr(argv, i, ft_strlen(argv));
	return (values);
}

void	add_exported(t_envp **envp, t_envp *new)
{
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	tmp->next = new;
}

t_envp	*make_exported(char *argv, t_shell *shell)
{
	t_envp	*new;
	char	*var;
	char	*values;
	
	var = get_var(argv);
	values = get_values(argv, shell);
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

int	check_export(char *opt_var, t_shell *shell) //var ou autre ?
{
	char	*values;

	printf("HAHA\n");
	printf("%s\n", opt_var);
	while (shell->envp)
	{
		if (!ft_strncmp(opt_var, shell->envp->var, ft_strlen(shell->envp->var)))
		{
			printf("LOL\n");
			values = get_values(opt_var, shell);
			printf("%s\n", values);
			free(shell->envp->values);
			shell->envp->values = ft_strdup(values);
			free(values);
			return (1);
		}
		if (shell->envp->next)
			shell->envp = shell->envp->next;
		else
			break ;
	}
	return (0);
}

void	export_var(t_shell *shell, t_envp *envp)
{
	t_envp	*new;
	int	check;

	if (shell->cmds->full_cmd[1] && ft_strchr(shell->cmds->full_cmd[1], '='))
	{
		check = check_export(shell->cmds->full_cmd[1], shell);
		if (!check)
		{
			printf("NANA\n");
			new = make_exported(shell->cmds->full_cmd[1], shell);
			add_exported(&envp, new);
		}
	}
	else if (!shell->cmds->full_cmd[1])
	{
		while (shell->envp)
		{
			printf("declare -x %s=\"%s\"\n", shell->envp->var, shell->envp->values); //declare -x ou export ?
			if (shell->envp->next)
				shell->envp = shell->envp->next;
			else
				break ;
		}
	}
}
