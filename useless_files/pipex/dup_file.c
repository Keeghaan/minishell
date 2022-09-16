/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:09:11 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/30 16:32:00 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	child_process(t_shell *child, int index, char **envp)
{
	close(child->fd[0]);
	if (index == child->n - 1)
	{
		printf("1 dup file child process 1/3\n"); //
		if (dup2(child->cmds->outfile, STDOUT_FILENO) == -1)
			ft_printf("dup_file 1 %s: %s\n", SH, strerror(errno));//
		printf("1 dup file child process 2/3\n"); //
		close(child->cmds->outfile);
		printf("1 dup file child process 3/3\n"); //
	}
	else if (index == 0)
	{
		printf("2 dup file child process 1/5\n"); //
		if (child->cmds->infile != -1)
		{
			printf("2 dup file child process 2/5\n"); //
			if (dup2(child->fd[1], STDOUT_FILENO) == -1)
				ft_printf("dup_file 2 %s: %s\n", SH, strerror(errno));//
			printf("2 dup file child process 3/5\n"); //
			printf("2 dup file child process 4/5\n"); //
		}
		printf("2 dup file child process 5/5 \n"); //
	}
	else
	{
		printf("3 dup file child process \n");//
		if (dup2(child->fd[1], STDOUT_FILENO) == -1)
			ft_printf("dup_file 3 %s: %s\n", SH, strerror(errno)); //
	}
	close(child->fd[1]);
	printf("test dup_.c\n");//

	printf("HHHHEEEEdup file chld process \n");//
	process(child, envp);
}

static void	pipex_loop2(t_shell *child, int i, char **envp)
{
/*	close(child->fd[0]);
	if (i == 0)
	{
		if (child->cmds->infile != -1)
			child_process(child, i, envp);
	}
	if (i > 0)*/
		child_process(child, i, envp);
}

static void	pipex_loop(t_shell *child, int i, char **envp)
{
	int	j;

	j = -1;
	printf("index %d / %d(cmd) (pipex_loop dup_file.c)\n", i, child->n);//
	printf("pipex loop %d i / %d infile\n", i, child->cmds->infile);
	if (i > 0)
	{
		if (dup2(child->fd[0], STDIN_FILENO) == -1)
			ft_printf("dup_file 4 %s: %s\n", SH, strerror(errno));//
		close(child->fd[0]);
	}
	if (pipe(child->fd) == -1)
		ft_printf("dup_file 5%s: %s\n", SH, strerror(errno)); //
	if (i == 0)
	{
		if (child->cmds->infile != -1)
			child->pid[i] = fork();
	}
	if (i > 0)
		child->pid[i] = fork();
	if (child->pid[i] == -1)
	{
		close_files(child->cmds);
		close_pipes(child);
		ft_printf("dup_file 6 %s: %s\n", SH, strerror(errno));//
	}
	if (child->pid[i] == 0 && child->cmds->infile > -1)
		pipex_loop2(child, i, envp);
/*	if (child->fd[0] > -1)
		close(child->fd[0]);
	if (child->cmds->infile > -1)
		close(child->cmds->infile);
	while (++j < child->n)
		waitpid(child->pid[j], NULL, 0);*/
}

void	process_pipex(t_shell *child, char **envp)
{
	int	i;

	i = -1;
	while (child->cmds)
	{
		if (child->cmds->prev)
			child->cmds = child->cmds->prev;
		else
			break ;
	}
	if (child->cmds->infile != -1)
	{
		if (dup2(child->cmds->infile, STDIN_FILENO) == -1)
			ft_printf("dup_file 7 %s: %s\n", SH, strerror(errno)); //
		close(child->cmds->infile);
	}
	while (++i < child->n)
	{
		pipex_loop(child, i, envp);
//		close(STDIN_FILENO);
//		close(child->fd[0]);
		close(child->fd[1]);
	}
	i = -1;
	if (child->fd[0] != -1)
		close(child->fd[0]);
	if (child->cmds->infile != -1)
		close(child->cmds->infile);
	while (++i < child->n)
		waitpid(child->pid[i], NULL, 0);
}
