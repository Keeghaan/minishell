/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:27:15 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/26 16:21:21 by nboratko         ###   ########.fr       */
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
	new->next = NULL;
	if (!new->values)
	{
		new->values = ft_strdup(" ");
		new->visible = 0;
	}
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
	if (values)
		new->values = ft_strdup(values);
	else
		new->values = NULL;
	new->visible = 1;
	if (var)
		free(var);
	if (values)
		free(values);
	return (new);
}

int	check_export(char *var, t_envp **envp, t_shell *shell)
{
	char	*values;
	t_envp	*tmp;

	tmp = *envp;
	while (tmp)
	{
		if (!ft_strncmp2(var, tmp->var, ft_strlen(tmp->var)))
		{
			values = get_values(var, shell);
			if (!values)
				return (2);
			free(tmp->values);
			tmp->values = ft_strdup(values);
			tmp->visible = 1;
			free(values);
			return (1);
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (0);
}

static void	print_export(t_shell *shell)
{
	t_envp	*tmp;

	tmp = shell->envp;
	while (tmp)
	{
		if (tmp->visible == 1)
			printf("declare -x %s=\"%s\"\n", tmp->var,
				tmp->values);
		else if (tmp->visible == 0)
			printf("declare -x %s\n", tmp->var);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}

void	export_var(t_shell *shell, t_envp *envp)
{
	t_envp	*new;
	int		check;

	(void)envp;
	if (shell->cmds->full_cmd[1])
	{
		check = check_export(shell->cmds->full_cmd[1], &shell->envp, shell);
		if (!check && check != 2)
		{
			new = make_exported(shell->cmds->full_cmd[1], shell);
			add_exported(&shell->envp, new);
		}
	}
	else if (!shell->cmds->full_cmd[1])
		print_export(shell);
}
