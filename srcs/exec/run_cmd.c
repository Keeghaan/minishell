/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:28:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/16 17:44:34 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_path_cmd2(char *cmd)
{
	int	j;

	j = -1;
	if (ft_strchr(cmd, '/'))
	{
		while (cmd[++j])
		{
			if (cmd[j] == '.')
				return (1);
		}
		if (access(cmd, F_OK | R_OK | X_OK) == 0)
			return (0);
		return (1);
	}
	return (2);
}

int	get_cmd_nbr(t_shell *shell, char **envp)
{
	int	n;

	n = 0;
	while (shell->token)
	{
		if (is_valid_cmd(shell->token->value, envp))
			n++;
		if (shell->token->next)
			shell->token = shell->token->next;
		else
			break ;
	}
	while (shell->token)
	{
		if (shell->token->prev)
			shell->token = shell->token->prev;
		else
			break ;
	}
	return (n);
}

int	path_builtins(t_shell *shell, t_cmd *cmd, int active)
{
	if (!ft_strncmp(cmd->full_cmd[0], "unset", ft_strlen(cmd->full_cmd[0])))
	{
		if (active)
			unset_envp(shell, cmd->full_cmd[1]);
		return (3);
	}
	if (!ft_strncmp(cmd->full_cmd[0], "env", ft_strlen(cmd->full_cmd[0])))
	{
		if (active)
			print_envp(shell->envp, cmd);
		return (4);
	}
	if (ft_strchr(cmd->full_cmd[0], '='))
	{
		if (active)
			fake_export(cmd->full_cmd[0], shell);
		return (5);
	}
	return (0);
}

int	is_it_builtin(t_shell *shell, t_cmd *cmd, int active)
{
	if (path_builtins(shell, cmd, active))
		return (1);
	if (!ft_strncmp(cmd->full_cmd[0], "cd", ft_strlen(cmd->full_cmd[0])))
	{
		if (active)
		{
			if (!cmd->full_cmd[1])
				return (cd_cmd(shell, NULL), 1);
			return (cd_cmd(shell, cmd->full_cmd[1]), 1);
		}
		return (1);
	}
	if (!ft_strncmp(cmd->full_cmd[0], "export", ft_strlen(cmd->full_cmd[0])))
	{
		if (active)
			export_var(shell, shell->envp);
		return (1);
	}
	if (!ft_strncmp(cmd->full_cmd[0], "pwd", ft_strlen(cmd->full_cmd[0])))
		return (2);
	if (!ft_strncmp(cmd->full_cmd[0], "echo", ft_strlen(cmd->full_cmd[0])))
		return (2);
	return (0);
}

void	run_cmd(t_shell *shell, char **envp)
{	
	int	cmd;

	cmd = 0;
	shell->n_cmds = get_cmd_nbr(shell, envp);
	while (shell->cmds)
	{
		is_it_builtin(shell, shell->cmds, 1);
		if (is_valid_cmd(shell->cmds->full_cmd[0], envp))
			cmd++;
		if (shell->cmds->next)
			shell->cmds = shell->cmds->next;
		else
			break ;
	}
	rewind_cmd(&shell->cmds, 1);
	if (ft_strlen(shell->env[0]) > 1)
	{
		error_msg(shell, shell->cmds, envp, 1);
		if (cmd)
		{
			signalisation(1);
			pipex(shell, envp);
		}
	}
}
