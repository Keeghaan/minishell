/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:07:52 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/19 20:03:56 by jcourtoi         ###   ########.fr       */
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
	int		not_found;

	j = -1;
	not_found = 1;
	if (!check_path_cmd2(cmd))
		return (0);
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
			not_found = 0;
		free(path);
	}
	return (not_found);
}

int	play_msg(int err, t_shell *shell, t_cmd *cmd, int msg)
{
	int	ret;

	ret = 0;
	if (err && !(is_it_builtin(shell, cmd, 0) == 1
			|| is_it_builtin(shell, cmd, 0) == 2))
	{
		ret++;
		if (msg)
		{
			if (cmd->empty)
				printf(": command not found\n");
			else
			{
				if (!is_a_dir(cmd->full_cmd[0]))
					printf("%s: command not found\n", cmd->full_cmd[0]);
			}
		}
		shell->ret = 127;
	}
	else
		shell->ret = 0;
	return (ret);
}

void	other(char *cmd, char **envp)
{
	int	dir;

	dir = is_a_dir(cmd);
	if (!is_valid_cmd(cmd, envp))
	{
		if (dir == 3)
			printf("%s: %s: %s\n", SH, cmd, strerror(21));
		else if (dir == 2 && ft_strchr(cmd, '/'))
			printf("%s: %s: %s\n", SH, cmd, strerror(path_found(cmd)));
		else if (dir == 2 && !ft_strchr(cmd, '/'))
			printf("%s: %s: command not found\n", SH, cmd);
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
		if ((!cmd->prev && !cmd->next) || (!cmd->prev && cmd->next))
			other(cmd->full_cmd[0], envp);
		err = check_errno(cmd->full_cmd[0], en);
		if (err > 0)
			ret += play_msg(err, shell, cmd, msg);
		if (cmd->next)
			cmd = cmd->next;
		else
			break ;
	}
	free_split(en);
	return (err);
}
