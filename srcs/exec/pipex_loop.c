/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:20:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/26 13:14:38 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	pipex_loop2(t_shell *child, int i, char **envp, t_envp **env)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close(child->pipefd[0]);
	if (i == 0)
	{
		if (child->infile != -1)
			child_process(child, i, envp, env);
	}
	if (i > 0)
		child_process(child, i, envp, env);
}

static void	pipex_loop_bis(t_shell *child, t_cmd *tmp)
{
	if (ft_strncmp(tmp->infile, "/dev/stdin", ft_strlen(tmp->infile)))
	{
		dup2(child->std_in, 0);
		child->infile = open(tmp->infile, O_RDONLY);
		if (child->infile > -1)
		{
			if (dup2(child->infile, STDIN_FILENO) == -1)
				printf("%s: %s\n", SH, strerror(errno));
			close(child->infile);
		}
	}
	else
	{
		if (dup2(child->pipefd[0], STDIN_FILENO) == -1)
			printf("%s: %s\n", SH, strerror(errno));
		close(child->pipefd[0]);
	}
}

static void	pipex_loop_ter(t_shell *child, int i, char **envp, t_envp **env)
{
	if (i == 0)
	{
		if (child->infile != -1)
			child->pid[i] = fork();
	}
	if (i > 0)
		child->pid[i] = fork();
	if (child->pid[i] == -1)
		printf("%s: %s\n", SH, strerror(errno));
	if (child->pid[i] == 0)
		pipex_loop2(child, i, envp, env);
}

void	pipex_loop(t_shell *child, int i, char **envp, t_envp **env)
{
	t_cmd	*tmp;
	int		j;

	tmp = child->cmds;
	if (i != 0)
	{
		j = 0;
		while (j < i)
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
			j++;
		}
	}
	if (i > 0)
		pipex_loop_bis(child, tmp);
	if (pipe(child->pipefd) == -1)
		ft_printf("%s: %s\n", SH, strerror(errno));
	pipex_loop_ter(child, i, envp, env);
}
