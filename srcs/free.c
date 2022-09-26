/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:42:41 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/25 21:39:02 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split(char **av)
{
	int	i;

	i = 0;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	free_exit(t_shell *shell, char *buf, int msg, int ret)
{
	free_token(&shell->token);
	free_envp(&shell->envp);
	if (buf)
		free(buf);
	if (msg)
		ft_putendl_fd("exit", 1);
	exit(ret);
}

void	free_cmds_bis(t_cmd *tmp)
{
	int	i;

	i = 0;
	while (tmp->full_cmd[i])
	{
		if (tmp->full_path && ft_strncmp(tmp->full_path,
				tmp->full_cmd[i], ft_strlen(tmp->full_path)))
			free(tmp->full_cmd[i]);
		if (!tmp->full_path)
			free(tmp->full_cmd[i]);
		i++;
	}
}

void	free_cmds(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp)
	{
		*cmd = (*cmd)->next;
		if (tmp->full_cmd[0] && !ft_strlen(tmp->full_cmd[0]))
			free(tmp->full_cmd[0]);
		else
			free_cmds_bis(tmp);
		if (tmp->full_path)
			free(tmp->full_path);
		free(tmp->full_cmd);
		free(tmp);
		tmp = *cmd;
	}
}

void	free_envp(t_envp **envp)
{
	t_envp	*tmp;
	t_envp	*alst;

	alst = *envp;
	while (alst)
	{
		tmp = alst;
		alst = alst->next;
		free(tmp->var);
		free(tmp->values);
		free(tmp);
	}
}
