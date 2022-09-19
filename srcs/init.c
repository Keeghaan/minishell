/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:06:36 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/19 20:11:55 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_shell(t_shell *shell)
{
	shell->infile = -1;
	shell->outfile = -1;
	shell->pipe = 0;
	shell->unclosed_q = 0;
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
}
