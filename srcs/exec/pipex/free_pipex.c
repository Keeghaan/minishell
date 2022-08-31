/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 15:34:08 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/26 15:36:58 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	close_files(t_cmd *cmd)
{
	if (cmd->infile > -1)
		close(cmd->infile);
	if (cmd->outfile > -1)
		close(cmd->outfile);
}

void	close_pipes(t_shell *shell)
{
	close(shell->fd[0]);
	close(shell->fd[1]);
}

void	free_cmd(t_cmd *cmd)
{
	int	j;

	j = -1;
	while (cmd)
	{
		while (cmd->full_cmd[++j])
			free(cmd->full_cmd[j]);
		free(cmd->full_cmd);
		if (cmd->full_path)
			free(cmd->full_path);
		if (cmd->infile > -1)
			close(cmd->infile);
		if (cmd->outfile > -1)
			close(cmd->outfile);
		if (cmd->next)
			cmd = cmd->next;
	}
//	free(cmd); ?
}

void	free_pipex(t_shell *shell)
{
	if (shell->heredoc)
		unlink(".heredoc");
	free(shell->pid);
//	free_cmd(shell->cmds);
	if (shell->pipe)
		close_pipes(shell);
}
