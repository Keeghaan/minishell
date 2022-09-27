/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_wait.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:49:58 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/26 16:19:06 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_wait(t_shell *child)
{
	int		i;
	t_cmd	*t;

	i = -1;
	t = child->cmds;
	rewind_cmd(&t, 0);
	while (++i < child->n_cmds)
	{
		waitpid(child->pid[i], &g_return, 0);
		if (g_return && is_valid_cmd(t->full_cmd[0], child->env) == 0)
			child->ret = 127;
		else if (WIFSIGNALED(g_return) && !child->ret)
			child->ret = 130;
		else if (g_return && !check_file(t->infile, 0))
			child->ret = 1;
		else
			child->ret = 0;
	}
}

void	malloc_pid(t_shell *child)
{
	int	i;

	child->pid = malloc(sizeof(int) * child->n_cmds);
	if (!child->pid)
		return ;
	i = -1;
	while (++i < child->n_cmds)
		child->pid[i] = -2;
}

int	path_builtins_bis(t_shell *shell, t_cmd *cmd, int active)
{
	if (!ft_strncmp(cmd->full_cmd[0], "cd", ft_strlen(cmd->full_cmd[0])))
	{
		shell->ret = 0;
		if (active)
		{
			if (!cmd->full_cmd[1])
			{
				if (cd_cmd(shell, NULL))
					shell->ret = 1;
			}
			else
			{
				if (cd_cmd(shell, cmd->full_cmd[1]))
					shell->ret = 1;
			}
		}
		return (1);
	}
	return (0);
}

int	get_nb_tokens(t_shell *shell)
{
	t_token	*token;
	int		i;

	i = 1;
	token = shell->token;
	while (token)
	{
		if (token->next)
			token = token->next;
		else
			break ;
		i++;
	}
	return (i);
}
