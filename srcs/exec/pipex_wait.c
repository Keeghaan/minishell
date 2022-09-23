/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:58 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/22 11:55:42 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_wait(t_shell *child)
{
	int		i;
	t_cmd	*t;

	i = -1;
	t = child->cmds;
	rewind_cmd(&t, 0);
	while (++i < child->n_cmds)
	{
		waitpid(child->pid[i], &g_return, 0);
		if (g_return && is_valid_cmd(t->full_cmd[0], child->env) == 0)
			child->ret = 127;
		else if (WIFSIGNALED(g_return))
			child->ret = 130;
		else if (g_return && !check_file(t->infile, 0))
			child->ret = 1;
		else
			child->ret = 0;
	}
}