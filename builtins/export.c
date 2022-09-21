/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:27:15 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/21 21:27:16 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	check_export(char *var, t_shell *shell)
{
	char	*values;

	while (shell->envp)
	{
		if (!ft_strncmp(var, shell->envp->var, ft_strlen(shell->envp->var)))
		{
			values = get_values(var, shell);
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
	int		check;

	if (shell->cmds->full_cmd[1] && ft_strchr(shell->cmds->full_cmd[1], '='))
	{
		check = check_export(shell->cmds->full_cmd[1], shell);
		if (!check)
		{
			new = make_exported(shell->cmds->full_cmd[1], shell);
			add_exported(&envp, new);
		}
	}
	else if (!shell->cmds->full_cmd[1])
	{
		while (shell->envp)
		{
			printf("declare -x %s=\"%s\"\n", shell->envp->var,
				shell->envp->values);
			if (shell->envp->next)
				shell->envp = shell->envp->next;
			else
				break ;
		}
	}
}
