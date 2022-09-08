/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:06:36 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/08 16:19:27 by jcourtoi         ###   ########.fr       */
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
