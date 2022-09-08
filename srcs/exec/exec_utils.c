/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:17:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/08 12:48:58 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Est ce une variable d'environnement ??
int	is_env_var(t_envp *envp, char *var)
{
	while (envp)
	{
		if (!ft_strncmp(envp->var, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(envp->var))
			return (1);
		if (envp->next)
			envp = envp->next;
		else
			break ;
	}
	return (0);
}

static int	join_path(char *tmp, char *path, char **en, char *cmd)
{
	if (!tmp)
		return (free_split(en), 0);
	path = ft_strjoin(tmp, cmd);
	if (!path)
		return (free(tmp), free_split(en), 0);
	free(tmp);
	return (1);
}

static int	is_valid_ter(char *cmd, char **envp, char *path)
{
	char	**en;
	char	*tmp;
	int		j;

	j = -1;
	if (!ft_isalpha(*cmd)) /// a verifier
		return (0);
	en = get_env(envp);
	if (!en)
		return (0);
	while (en[++j])
	{
		if (en[j])
		{
			tmp = ft_strjoin(en[j], "/");
			if (!join_path(tmp, path, en, cmd))
				return (-1);
			if (access(path, R_OK | X_OK) == 0)
				return (free(path), free_split(en), 1);
			free(path);
		}
	}
	return (free_split(en), 0);
}

static	int	valid_cmd_bis(char *cmd)
{
	int	j;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j++] == '.')
			return (0);
	}
	return (1);
}

int	is_valid_cmd(char *cmd, char **envp)
{
	char	*path;

	path = NULL;
	if (!valid_cmd_bis(cmd))
		return (0);
	if (!check_path_cmd2(cmd))
	{
		path = ft_strdup(cmd);
		if (access(path, R_OK | X_OK) == 0)
			return (1);
		return (free(path), 0);
	}
	else
	{
		if (!is_valid_ter(cmd, envp, path))
			return (1);
	}
	return (0);
}
