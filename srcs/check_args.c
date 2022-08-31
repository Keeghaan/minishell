/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:35:22 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/16 16:27:59 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env(char **envp)
{
	int	i;
	char	**en;
	char	*tmp;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			tmp = ft_strchr(envp[i], '/');
			break ;
		}
		i++;
	}
	en = ft_split(tmp, ':');
	if (!en)
		return (NULL);
	return (en);
}

static char	*check_path_cmd(int i, char *cmd)
{
	char	**split;
(void)i;
	
	split = ft_split(cmd, ' ');
	if (!split)
		return (NULL);
	if (ft_strchr(split[0], '/'))
	{
		if (access(split[0], F_OK | X_OK | R_OK) == 0)
			return (NULL);
		return (NULL);
	}
	return (split[0]);
}

static char	*ret_path(int i, char *cmd, char **en)
{
	char	*cmd_path;
	char	*tmp;

	tmp = NULL;
	cmd_path = NULL;
	cmd_path = check_path_cmd(0, cmd);
	if (!cmd_path)
		cmd_path = ft_strdup(cmd);
	else
	{
		tmp = ft_strjoin(en[i], "/");
		cmd_path = ft_strjoin(tmp, cmd_path);
		free(tmp);
	}
	if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
		return (cmd_path);
	free(cmd_path);
	return (NULL);
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
		i++;
	}
	return (cmd_path);
}

int	check_argv(int ac, char **av, char **en)
{
	int	j;
	char	*tmp;
	char	**envp;
	
	j = 1;
	envp = get_env(en);
	if (!envp)
		return (3);
	if (ac > 1)
	{
		while (av[j])
		{
			tmp = get_path_cmd(envp, av[j]);
			if (access(tmp, F_OK | R_OK | X_OK) == 0)
				return (printf("%s: cannot execute binary file\n", tmp), 1);
			else
				return (printf("%s: %s\n", av[j], strerror(2)), 2);
			j++;
		}
	}
	free_split(envp);
	return (0);
}
