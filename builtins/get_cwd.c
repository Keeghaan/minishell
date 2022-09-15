/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:00:56 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/15 16:05:03 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_next_dir(t_shell *shell, char *dir)
{
	char	*tmp;
	char	*tmp2;

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
