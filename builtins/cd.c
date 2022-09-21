/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:45:38 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/21 19:32:38 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_pre_cd(t_shell *shell)
{
	if (get_nb_tokens(shell) == 1)
		return (0);
	if (shell->token->type == REDIR_IN && shell->token->next)
	{
		if (!check_file(shell->token->next->value, 0))
			return (1);
	}
	else if (ft_strncmp(shell->cmds->full_cmd[0], "cd", 3) != 0)
	{
		if (!is_valid_cmd(shell->cmds->full_cmd[0], shell->env))
			return (2);
	}
	return (0);
}

int	possibilities(t_shell *shell, char *action)
{
	char	*user;
	char	*home;

	if (!action)
	{
		if (check_pre_cd(shell))
			return (0);
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

	if (action && !check_file(action, 1))
		return (8);
	oldpwd = ft_strdup(shell->cwd);
	if (!oldpwd)
		return (5);
	move = possibilities(shell, action);
	if (!move)
		return (free(oldpwd), 1);
	if (move == 4)
	{
		if (chdir(shell->next_dir) != 0)
			return (free(oldpwd), 3);
	}
	getcwd(shell->cwd, sizeof(shell->cwd));
	pwd = ft_strdup(shell->cwd);
	if (!pwd)
		return (4);
	change_pwd(&shell->envp, oldpwd, pwd);
	return (0);
}
