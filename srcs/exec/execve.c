/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 16:32:39 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/08 16:23:14 by jcourtoi         ###   ########.fr       */
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
	/*t_token *tmp;
	int		ret;

	tmp = *token;
	ret = 0;
	while (tmp)
	{
		if (tmp->type == REDIR_IN && tmp->next)
		{
			cmd->infile = open(tmp->next->value, O_RDONLY);
			if (cmd->infile < 0)
				return (printf("%s: %s: %s\n", SH, tmp->next->value, strerror(errno)), 0);
			ret++;
		}
		if (tmp->type == REDIR_OUT && tmp->next)
		{
			cmd->outfile = open(tmp->next->value, O_RDWR | O_TRUNC | O_CREAT, 0644);
			if (cmd->outfile < 0)
				return (printf("%s: %s: %s\n", SH, tmp->next->value, strerror(errno)), 0);
			ret++;
		}
		if (tmp->type == DREDIR_OUT && tmp->next)
		{
			cmd->outfile = open(tmp->next->value, O_RDWR | O_APPEND | O_CREAT, 0644);
			if (cmd->outfile < 0)
				return (printf("%s: %s: %s\n", SH, tmp->next->value, strerror(errno)), 0);
			ret++;
		}
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	return (ret);*/
}

void	exec_cmd(t_shell *shell, char *path, char **envp)
{
//	struct sigaction	s;

//	ft_memset(&s, 0, sizeof(s));
//	s.sa_handler = SIG_DFL;
//	s.sa_handler = &handle_sigint; //test
	signalisation(1);
	if (shell->pipe)
	{
		shell->pipe = 1;
		rewind_cmd(&shell->cmds, 1);
		pipex(shell);
	}
	else if (!shell->pipe && shell->n_cmds)
	{
		get_files(shell);
		//shell->infile = 0;
		//shell->outfile = 1;
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
	}
}
