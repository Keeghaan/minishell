/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:06:36 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/18 15:38:41 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_shell(t_shell *shell)
{
	shell->infile = -1;
	shell->outfile = -1;
	shell->pipe = 0;
	shell->ret = 0;
	shell->prev_dir = NULL;
	shell->next_dir = NULL;
}

void	init_shell_struct(t_shell *shell)
{
	t_cmd	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (tmp->redir == 1)
		shell->outfile = open(tmp->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->redir == 2)
		shell->outfile = open(tmp->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
}
