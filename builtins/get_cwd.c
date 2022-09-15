/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:00:56 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/15 13:08:04 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_next_dir(t_shell *shell, char *dir)
{
	char	*tmp;
	char	*tmp2;
	char	*user;
	char	*home;

	user = expand_env_var("USER", &shell->envp, 0);
	if (!user)
		return (1);
	home = ft_strjoin("/home/", user);
	if (!home)
		return (free(user), 1);
	if (ft_strncmp(dir, home, ft_strlen(dir)) == 0)
	{
		shell->next_dir = ft_strjoin("/mnt/nfs/homes/", user); //pas obligatoire
		if (!shell->next_dir)
			return (free(home), free(user), 1);
		printf("%s\n", shell->next_dir); //
		return (free(home), free(user), 0);
	}
	free(home);
	free(user);
	if (ft_strchr(dir, '/'))
	{
		if (access(dir, F_OK | R_OK) == 0)
		{	
			shell->next_dir = ft_strdup(dir);
			return (0);
		}
	}
	if (*dir != '/')
	{
		tmp = ft_strjoin(shell->cwd, "/");
		if (!tmp)
			return (1);
	}
	else
		tmp = ft_strdup(dir);
	tmp2 = ft_strjoin(tmp, dir);
	if (!tmp2)
		return (free(tmp), 2);
	shell->next_dir = ft_strdup(tmp2);
	if (!shell->next_dir)
		return (free(tmp2), free(tmp), 2);
	free(tmp2);
	free(tmp);
	return (0);
}

int	get_cwd(t_shell *shell)
{
	getcwd(shell->cwd, sizeof(shell->cwd));
	if (errno)
		return (2);
	if (get_next_dir(shell, NULL))
		return (free(shell->prev_dir), 4);
	return (0);
}
