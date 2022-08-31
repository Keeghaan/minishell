/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:14:28 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/30 15:51:09 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	pipex(t_shell *shell, char **envp)
{
	printf("in %d\nout %d\n", shell->cmds->infile, shell->cmds->outfile);
	(void)envp;
	process_pipex(shell, envp);
	printf("pipex.c (process_pipex ended)\n");
}
