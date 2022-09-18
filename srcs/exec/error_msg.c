/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:07:52 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/18 14:44:06 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	path_found(char *cmd)
{
	if (access(cmd, R_OK | X_OK | F_OK) == 0)
		return (0);
	return (errno);
}

static int	check_errno(char *cmd, char **en)
{
	char	*path;
	char	*tmp;
	int		j;
	int		found;

	j = -1;
	found = 0;
	if (!check_path_cmd2(cmd))
		return (path_found(cmd));
	while (en[++j])
	{
		tmp = ft_strjoin(en[j], "/");
		if (!tmp)
			return (-1);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (-2);
		if (access(path, F_OK | X_OK | R_OK) == 0)
			found++;
		free(path);
	}
	if (!found)
		return (errno);
	return (0);
}

int	play_msg(int err, t_shell *shell, t_cmd *cmd, int msg)
{
	int	ret;

	ret = 0;
	if (err && !(is_it_builtin(shell, cmd, 0) == 1))
	{
		ret++;
		if (msg)
		{
			if (cmd->empty)
				printf(": command not found\n");
			else
				printf("%s: command not found\n", cmd->full_cmd[0]);
		}
	}
	return (ret);
}

int	error_msg(t_shell *shell, t_cmd *cmd, char **envp, int msg)
{
	char	**en;
	int		err;
	int		ret;

	ret = 0;
	en = get_env(envp);
	if (!en)
		return (-1);
	while (cmd)
	{
		err = check_errno(cmd->full_cmd[0], en);
		ret += play_msg(err, shell, cmd, msg);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	free_split(en);
	return (err);
}
