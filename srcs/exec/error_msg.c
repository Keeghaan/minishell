/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:07:52 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/07 18:04:47 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
/*
void	error_msg(t_cmd *cmd)
{
	while (cmd)
	{
		if (access(cmd->full_path, F_OK | X_OK | R_OK) != 0)
			printf("%s: %s: %s\n", SH, cmd->full_cmd[0], strerror(errno));
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
}

*/

static int	check_errno(char *cmd, char **en)
{
	char	*path;
	char	*tmp;
	int		j;
	int		found;

	j = -1;
	found = 0;
	while (en[++j])
	{
		tmp = ft_strjoin(en[j], "/");
		if (!tmp)
			return (-1);
		path = ft_strjoin(tmp, cmd);
		if (!path)
			return (-2);
		if (access(path, F_OK | X_OK | R_OK) == 0)
			found++;
	}
	if (!found)
		return (errno);
	return (0);
}

int	cmd_not_fnd(char *path, char **en)
{
	(void)en;
	char	*cmd;
	int		found;

	found = 0;
	if (access(path, F_OK | X_OK | R_OK) == 0)
		found++;
	cmd = ft_strrchr(path, '/');
	if (!found)
		return (printf("%s: command not found\n", cmd), 1);
	return (0);
}

void	error_msg(t_cmd *cmd, char **envp)
{
	char	**en;
	int		err;

	en = get_env(envp);
	if (!en)
		return ;
	while (cmd)
	{
		err = check_errno(cmd->full_cmd[0], en);
		if (err)
			printf("%s: command not found\n", cmd->full_cmd[0]);	
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	free_split(en);
}
