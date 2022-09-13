/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:35:22 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/13 14:56:30 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_env(char **envp)
{
	int	i;
	char	**en;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
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

static char	*check_path_cmd(int i, char *cmd)
{
(void)i;
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
	if (check_path_cmd(0, cmd))
		cmd_path = ft_strdup(cmd); //juste pour le malloc pour le free du bas
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

int	check_argv(t_shell *shell, int ac, char **av, char **en)
{
//	(void)shell;
	char	*tmp;
//	char	**envp;

	tmp = NULL;
	shell->env = get_env(en);
	if (!shell->env)
	{
	//	shell->env_i = 1; a voir ?
		return (3);
	}
	if (ac > 1)
	{
		if (av[1])
		{
			tmp = get_path_cmd(shell->env, av[1]);
			if (!tmp)
				printf("%s: %s\n", av[1], strerror(2));
			else if (access(tmp, F_OK | R_OK | X_OK) == 0)
				printf("%s: %s: cannot execute binary file\n", tmp, tmp); //a voir si on l'affiche deux fois omme bash
		}
	}
	if (tmp)
		free(tmp);
	return (0);
}
