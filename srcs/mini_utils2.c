/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:28:11 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/20 17:21:14 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_redir(t_token *t)
{
	if (t->prev && !t->prev->prev && t->prev->type == WORD
		&& t->next && t->next->type == PIPE)
		return (1);
	return (0);
}

int	is_a_dir(char *value)
{
	int	fd;

	fd = open(value, O_RDWR);
	if (fd >= 0)
		return (close(fd), 2);
	fd = open(value, O_RDONLY);
	if (fd >= 0)
		return (close(fd), 3);
	return (0);
}

void	pipex_quatro(t_shell *child, char **envp)
{
	int	i;

	i = -1;
	while (++i < child->n_cmds)
	{
		pipex_loop(child, i, envp);
		close(STDIN_FILENO);
		close(child->pipefd[1]);
	}
}

void	shell_loop_ter(t_shell *shell, t_token **tok)
{
	int	cases;

	if (shell->cmds)
	{
		init_shell_struct(shell);
		if (!shell->unclosed_q)
			run_cmd(shell, shell->env);
	}
	else
	{
		cases = which_case(tok);
		if (cases == 1)
			shell->ret = 1;
		else
			shell->ret = 0;
	}
}
