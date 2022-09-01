/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:00:56 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/01 13:27:18 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_next_dir(t_shell *shell, char *dir)
{
	char	*tmp;
	char	*tmp2;

	if (shell->next_dir)
		free(shell->next_dir);
	tmp = ft_strjoin(shell->cwd, "/");
	if (!tmp)
		return (1);
	tmp2 = ft_strjoin(tmp, dir);
	if (!tmp2)
		return (free(tmp), 2);
	shell->next_dir = ft_strdup(tmp2);
	free(tmp2);
	free(tmp);
	return (0);
}

static int	back_func(t_shell *shell, char *del, int size, int back)
{
	char	*tmp;
	char	*tmp2;

	tmp = malloc(sizeof(char) * size + 1);
	tmp2 = ft_strdup(shell->cwd);
	if (back)
	{
		while (--back >= 0)
		{
			ft_strlcpy(tmp, tmp2, ft_strlen(tmp2) - ft_strlen(del) + 1);
			if (!back)
			{
				if (chdir(tmp) != 0)
					return (printf("%s: %s\n", tmp, strerror(errno)), free(tmp), 1);
				getcwd(shell->cwd, sizeof(shell->cwd));
				size = ft_strlen(tmp) - ft_strlen(del);
			}
			free(tmp2);
			tmp2 = ft_strdup(tmp);
			del = ft_strrchr(tmp, '/');
			if (!del)
				return (free(tmp), 1);	
		}
	}
	return (free(tmp), 0);
}

int	get_prev_dir(t_shell *shell, int back)
{
	char	*del;
	int		size;

	del = ft_strrchr(shell->cwd, '/');
	if (!del)
		return (1);
	size = ft_strlen(shell->cwd) - ft_strlen(del);
	if (back_func(shell, del, size, back))
		return (2);
	shell->prev_dir = malloc(sizeof(char) * (size + 1));
	if (!shell->prev_dir)
		return (3);
	ft_strlcpy(shell->prev_dir, shell->cwd, size + 1);
	return (0);
}

int	get_cwd(t_shell *shell)
{
	getcwd(shell->cwd, sizeof(shell->cwd));
	if (errno)
		return (2);
	if (get_prev_dir(shell, 0))
		return (3);
	if (get_next_dir(shell, NULL))
		return (4);
	return (0);
}
