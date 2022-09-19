/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:45:38 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/19 14:54:24 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	possibilities(t_shell *shell, char *action)
{
	char	*user;
	char	*home;

	if (!action)
	{
		user = expand_env_var("USER", &shell->envp, 0);
		home = ft_strjoin("/mnt/nfs/homes/", user);
		if (!home)
			return (0);
		if (chdir(home) != 0)
			return (0);
		return (free(home), free(user), 2);
	}	
	if ((ft_strlen(action) == 2 && ft_strnstr(action, "./", 2))
		|| (ft_strlen(action) == 1 && *action == '.'))
		return (1);
	get_next_dir(shell, action);
	if (access(shell->next_dir, F_OK | X_OK) != 0)
		return (printf("%s: %s: %s: %s\n", SH, "cd",
				action, strerror(errno)), 0);
	return (4);
}

void	change_pwd(t_envp **envp, char *oldpwd, char *pwd)
{
	t_envp	*en;

	en = *envp;
	while (en)
	{
		if (!ft_strncmp(en->var, "OLDPWD", ft_strlen(en->var))
			&& ft_strlen(en->var) == 6)
		{
			free(en->values);
			en->values = oldpwd;
		}
		else if (!ft_strncmp(en->var, "PWD", ft_strlen(en->var))
			&& ft_strlen(en->var) == 3)
		{
			free(en->values);
			en->values = pwd;
		}
		if (!en->next)
			break ;
		en = en->next;
	}
}

int	cd_cmd(t_shell *shell, char *action)
{
	int		move;
	char	*pwd;
	char	*oldpwd;

	oldpwd = ft_strdup(shell->cwd);
	move = possibilities(shell, action);
	if (!move)
		return (1);
	if (move == 4)
	{
		if (chdir(shell->next_dir) != 0)
			return (free(oldpwd), 3);
	}
	get_cwd(shell);
	pwd = ft_strdup(shell->cwd);
	change_pwd(&shell->envp, oldpwd, pwd);
	return (0);
}
