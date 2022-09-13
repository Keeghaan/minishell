/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:32:39 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/13 15:45:23 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_files(t_shell *shell) //cmd par shell
{
	shell->infile = open(shell->cmds->infile, O_RDONLY);
	if (shell->infile < 0)
	{
		printf("%s: %s: %s\n", SH, shell->cmds->infile, strerror(errno));
		if (!error_msg(shell, shell->cmds, shell->env, 0))
			g_return = 1;
	}
	else
	{
		if (dup2(shell->infile, STDIN_FILENO) == -1)
			printf("%s: %s: %s\n", SH, shell->cmds->infile, strerror(errno));
		close(shell->infile);
	}
}

void	exec_cmd(t_shell *shell, char *path, char **envp)
{
(void)path, (void)envp;
	signalisation(1);
//	if (shell->pipe)
//	{
	//	shell->pipe = 1;
		rewind_cmd(&shell->cmds, 1);
		pipex(shell);
/*	}
	else if (!shell->pipe && shell->n_cmds)
	{
		get_files(shell);
		shell->pid = malloc(sizeof(pid_t));
		if (!shell->pid)
			return ;
		shell->pid[0] = fork();
		if (shell->pid[0] < 0)
			return ;
		if (shell->pid[0] == 0)
		{
			//sigaction(SIGQUIT, &s, NULL);
			if (shell->infile > 0)
			{
				dup2(shell->infile, 0);
				close(shell->infile);
			}
			if (shell->outfile > -1)
			{
				dup2(shell->outfile, 1);
				close(shell->outfile);
			}
			if (cmd_not_fnd(path, envp))
				return ;
			if (ft_strncmp(shell->cmds->full_cmd[0], "env", ft_strlen(shell->cmds->full_cmd[0]) != 0))
               			 execve(path, shell->cmds->full_cmd, envp);
			//printf("failed ?"); //
		}
		waitpid(shell->pid[0], NULL, 0);
		free(shell->pid);
	}*/
}
