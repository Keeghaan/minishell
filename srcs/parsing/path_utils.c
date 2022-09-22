/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:23:03 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/22 12:32:46 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_builtin(t_token **tmp)
{
	if (!ft_strncmp((*tmp)->value, "echo", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "cd", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "unset", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "export", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "pwd", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "exit", ft_strlen((*tmp)->value)))
		return (1);
	return (0);
}

char	**get_paths(t_shell *shell, char *cmd, t_envp **envp)
{
	char	**paths;
	t_envp	*tmp;

	tmp = *envp;
	while (tmp && ft_strncmp(tmp->var, "PATH", 4))
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}	
	if (tmp == NULL || !ft_strncmp(tmp->var, "LD", 2) || !tmp->next)
	{
		shell->env[0] = "";
		shell->env[1] = "";
		ft_printf("minishell: %s: %s\n", cmd, "No such file or directory");
		return (NULL);
	}
	paths = NULL;
	if (tmp)
		paths = ft_split(tmp->values, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*get_full_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*slash;
	char	*path;
	int		i;

	i = 0;
	if (cmd && ft_strnstr(cmd, "/", ft_strlen(cmd))
		&& access(cmd, X_OK | F_OK | R_OK) == 0)
		return (cmd);
	paths = get_paths(shell, cmd, &shell->envp);
	if (!paths)
		return (NULL);
	while (paths[i++])
	{
		slash = ft_strjoin_original(paths[i], "/");
		path = ft_strjoin_original(slash, cmd);
		free(slash);
		if (!path)
			return (free_split(paths), NULL);
		if (access(path, X_OK | F_OK | R_OK) == 0)
			return (free_split(paths), path);
		free(path);
	}
	free_split(paths);
	return (NULL);
}
