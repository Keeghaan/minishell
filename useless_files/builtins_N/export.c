#include "../inc/minishell.h"

t_envp	*add_exported(t_envp **env, char *var, char *values)
{
	t_envp	*new;
	
	new = malloc(sizeof(envp));
	new->var = ft_strdup(var);
	new->values = ft_strdup(values);
	new->next = NULL;
	return (new);
}

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
