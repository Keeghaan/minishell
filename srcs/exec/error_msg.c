/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:07:52 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/08 16:54:25 by jcourtoi         ###   ########.fr       */
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

static int	path_found(char *cmd)
{
	if (access(cmd, R_OK | X_OK | F_OK) == 0)
		return (0);
//	printf("%s: command not found\n", cmd);
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

int	play_msg(int err, t_shell *shell, t_cmd *cmd, int msg)
{
	int	ret;

	ret = 0;
	if (err && !(is_it_builtin(shell, cmd, 0) == 1)) // a verifier
	{
		ret++;
		if (msg)
			printf("%s: command not found\n", cmd->full_cmd[0]);
	}
	return (ret);
}

void	ret_value(int err, int ret, t_shell *shell, int msg)
{
	if (!msg)
	{
		if (err && ret == 1)
			shell->ret = 127;
		else if (!err && shell->infile < 2)
			shell->ret = 1; //a verfiier
		else
			shell->ret = 0;
	}
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
		{
			if (!msg)
			{
				if (err && ret == 1)
					shell->ret = 127;
				else if (!err && shell->infile < 2)
					shell->ret = 1; //a verfiier
				else
					shell->ret = 0;
			}
		//	ret_value(err, ret, shell, msg);
			break ;
		}
	}
	free_split(en);
	return (err);
}
