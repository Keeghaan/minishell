/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:35:22 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/22 18:48:22 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_env(char **envp)
{
	int		i;
	char	**en;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		if (ft_strncmp2(envp[i], "PATH=", 5) == 0)
		{
			tmp = ft_strchr(envp[i], '/');
			break ;
		}
		i++;
	}
	if (tmp)
	{
		en = ft_split(tmp, ':');
		if (!en)
			return (NULL);
	}
	else
		return (NULL);
	return (en);
}

static char	*check_path_cmd(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK | X_OK | R_OK) == 0)
			return (cmd);
	}
	return (NULL);
}

static char	*ret_path(int i, char *cmd, char **en)
{
	char	*cmd_path;
	char	*tmp;

	tmp = NULL;
	cmd_path = NULL;
	if (check_path_cmd(cmd))
		cmd_path = ft_strdup(cmd);
	else
	{
		tmp = ft_strjoin(en[i], "/");
		if (!tmp)
			return (NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
			return (NULL);
	}
	if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
		return (cmd_path);
	return (free(cmd_path), NULL);
}

static char	*get_path_cmd(char **en, char *cmd)
{
	char	*cmd_path;
	int		i;

	cmd_path = NULL;
	i = 0;
	while (en[i])
	{
		cmd_path = ret_path(i, cmd, en);
		if (cmd_path != NULL)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

int	check_argv(int ac, char **av, char **envp)
{
	char	*tmp;
	char	**env;

	tmp = NULL;
	env = get_env(envp);
	if (!env)
		return (3);
	if (ac > 1)
	{
		if (av[1])
		{
			tmp = get_path_cmd(env, av[1]);
			if (!tmp)
				printf("%s: %s\n", av[1], strerror(2));
			else if (access(tmp, F_OK | R_OK | X_OK) == 0)
				printf("%s: %s: cannot execute binary file\n", tmp, tmp);
		}
	}
	if (tmp)
		free(tmp);
	return (free_split(env), 0);
}
