/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:42:41 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/20 15:57:52 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_global_return(t_token **token)
{
	free((*token)->value);
	(*token)->value = ft_itoa(g_return);
}

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

void	free_exit(t_shell *shell, char *buf, int msg)
{
	free_token(&shell->token);
	free_envp(&shell->envp);
	if (buf)
		free(buf);
	if (msg)
		ft_putendl_fd("exit", 1);
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
