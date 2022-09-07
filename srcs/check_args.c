/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 11:35:22 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/07 13:54:02 by jcourtoi         ###   ########.fr       */
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
//	if (tmp)
//	{
		en = ft_split(tmp, ':');
		if (!en)
			return (NULL);
//	}
//	else
//		return (NULL);
	return (en);
}

static char	*check_path_cmd(int i, char *cmd)
{
	char	**split;
	char	*ret;
(void)i;
	
	split = ft_split(cmd, ' ');
	if (!split)
		return (NULL);
	if (ft_strchr(split[0], '/'))
	{
		if (access(split[0], F_OK | X_OK | R_OK) == 0)
			return (free_split(split), NULL); //j'ai  note NULL je sais pas pourquoi 
		return (free_split(split), NULL);
	}
	ret = ft_strdup(split[0]);
	free_split(split);
	return (ret);
}

static char	*ret_path(int i, char *cmd, char **en)
{
	char	*cmd_path;
	char	*tmp;

	tmp = NULL;
	cmd_path = NULL;
	cmd_path = check_path_cmd(0, cmd);
	if (!cmd_path)
	{
		printf("ret path check args cmd %s\n", cmd); // pck je comprends pas mon check path cmd)
		cmd_path = ft_strdup(cmd);
	}
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
		free(cmd_path);
		i++;
	}
	return (NULL);
}

int	check_argv(int ac, char **av, char **en)
{
	char	*tmp;
	char	**envp;

	tmp = NULL;	
	envp = get_env(en);
	if (!envp)
		return (3);
	if (ac > 1)
	{
		if (av[1])
		{
			tmp = get_path_cmd(envp, av[1]);
			if (!tmp)
				printf("%s: %s\n", av[1], strerror(2));
			else if (access(tmp, F_OK | R_OK | X_OK) == 0)
				printf("%s: cannot execute binary file\n", tmp);
		}
	}
	if (tmp)
		free(tmp);
	free_split(envp);
	return (0);
}
