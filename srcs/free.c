/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:42:41 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/18 15:38:24 by jcourtoi         ###   ########.fr       */
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

void	free_exit(t_shell *shell)
{
	free_token(&shell->token);
	free_envp(&shell->envp);
	free_split(shell->env);
	exit(0);
}

void	free_cmds(t_cmd **cmd)
{
	t_cmd	*tmp;
	int		i;

	tmp = *cmd;
	while (tmp)
	{
		i = 0;
		*cmd = (*cmd)->next;
		while (tmp->full_cmd[i])
		{
			if (tmp->full_path && ft_strncmp(tmp->full_path,
					tmp->full_cmd[i], ft_strlen(tmp->full_path)))
				free(tmp->full_cmd[i]);
			if (!tmp->full_path)
				free(tmp->full_cmd[i]);
			i++;
		}
		if (tmp->full_path)
			free(tmp->full_path);
		free(tmp->full_cmd);
		if (tmp)
			free(tmp);
		tmp = *cmd;
	}
}
