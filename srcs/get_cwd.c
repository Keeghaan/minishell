/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:00:56 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/29 14:56:52 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_next_dir(t_shell *shell, char *dir)
{
	char	*tmp;
	char	*tmp2;

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

int	get_prev_dir(t_shell *shell, int back)
{
	char	*del;
	char	*tmp;

	del = ft_strrchr(shell->cwd, '/');
	if (!del)
		return (1);
	tmp = NULL;
	if (back)
	{
		while (--back)
		{
			ft_strlcpy(tmp, shell->cwd, ft_strlen(shell->cwd) - ft_strlen(del) + 1);
			del = ft_strrchr(shell->cwd, '/');
			if (!del)
				return (1);
		}
	}
	shell->prev_dir = malloc(sizeof(char)
			* ft_strlen(shell->cwd) - ft_strlen(del) + 1);
	if (!shell->prev_dir)
		return (2);
	ft_strlcpy(shell->prev_dir, shell->cwd,
		ft_strlen(shell->cwd) - ft_strlen(del) + 1);
	printf("%s\n", shell->prev_dir);
	return (0);
}

int	get_cwd(t_shell *shell)
{
	getcwd(shell->cwd, sizeof(shell->cwd));
	if (errno)
		return (free(shell->cwd), 2);
	if (get_prev_dir(shell, 0))
		return (free(shell->cwd), 3);
	if (get_next_dir(shell, "libft"))
		return (free(shell->next_dir), free(shell->cwd), 4);
	printf("%s\n%s\n%s\n", shell->cwd, shell->prev_dir, shell->next_dir); //
	return (0);
}
