/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:28:11 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/19 20:08:22 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_dir(char *value)
{
	int	fd;

	fd = open(value, O_RDWR);
	if (fd >= 0)
		return (close(fd), 2);
	fd = open(value, O_RDONLY);
	if (fd >= 0)
		return (close(fd), 3);
	return (0);
}

void	pipex_quatro(t_shell *child, char **envp)
{
	int	i;

	i = -1;
	while (++i < child->n_cmds)
	{
		pipex_loop(child, i, envp);
		close(STDIN_FILENO);
		close(child->pipefd[1]);
	}
}
