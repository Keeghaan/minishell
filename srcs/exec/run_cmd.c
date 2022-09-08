/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:28:32 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/08 13:03:54 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//test
int	check_path_cmd2(char *cmd)
{
	int 	j;

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
/*
int	is_cmd(t_shell *shell, char *cmd, char **envp)
{
	int		j;
	char	**en;
	char	*tmp;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j++] == '.')
			return (0);
	}
	if (!check_path_cmd2(cmd))
	{
		shell->cmds->full_path = ft_strdup(cmd);
		if (access(shell->cmds->full_path, R_OK | X_OK) == 0)
			return (1);
		return (free(shell->cmds->full_path), 0);
	}
	else
	{
		en = get_env(envp);
		while (en[j])
		{
			tmp = ft_strjoin(en[j], "/");//a proteger
			shell->cmds->full_path = ft_strjoin(tmp, cmd);//a protger
			free(tmp);
			if (access(shell->cmds->full_path, R_OK | X_OK) == 0)
				return (1);
			free(shell->cmds->full_path);
			j++;
		}
	}
	return (0);
}*/

int	get_cmd_nbr(t_shell *shell, char **envp)
{
	int	n;

	n = 0;
	while (shell->token)
	{
	//	printf("get cmd nbr %s\n", shell->token->value);
		if (is_valid_cmd(shell->token->value, envp))
			n++;
		if (shell->token->next)
			shell->token = shell->token->next;
		else
			break ;
	}
//	printf("%d get cmd nbr\n", n);
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
		return (2);
	}
	if (!ft_strncmp(cmd->full_cmd[0], "unset", ft_strlen(cmd->full_cmd[0])))
		return (3);
	return (0);
}
	
//cette fonction ne m'a pas l'air si utile (a par pour le cd);
int	is_it_builtin(t_shell *shell, t_cmd *cmd, int active)
{
	if (path_builtins(shell, cmd, active))
		return (1);
	else
	{
		if (!ft_strncmp(cmd->full_cmd[0], "env", ft_strlen(cmd->full_cmd[0])))
			return (2);
		if (!ft_strncmp(cmd->full_cmd[0], "pwd", ft_strlen(cmd->full_cmd[0])))
			return (2);
		if (!ft_strncmp(cmd->full_cmd[0], "echo", ft_strlen(cmd->full_cmd[0])))
			return (2);
	}
	return (0);
}
/*
int	what_is_it(t_shell *shell, t_cmd **cmds)
{
	int	j;
	int	result;

	j = 0;
	printf("what is it %s full cmd\n", (*cmds)->full_cmd[0]);
	rewind_cmd(cmds, 1);
	printf("what is it %s full cmd\n", (*cmds)->full_cmd[0]);
	while (*cmds)
	{
		result = is_it_builtin(shell, *cmds, j);
		if (result)
			return (2);//	result = run_builtin(result);
		else
			printf("%s not builtin\n", (*cmds)->full_cmd[0]);//result = 	//verifier si ce sont des files
		if ((*cmds)->next)
			(*cmds) = (*cmds)->next;
		else
			break ;
		j++;
	}
	return (result);
}*/

void	run_cmd(t_shell *shell, char **envp)
{	
	int	cmd;
	
	cmd = 0;
	shell->n_cmds = get_cmd_nbr(shell, envp);
	while (shell->cmds)
	{
		is_it_builtin(shell, shell->cmds, 1);
	//	if (!shell->cmds->full_path)
	//	{
	//		if (is_cmd(shell, shell->cmds->full_cmd[0], envp))
	//			cmd++;
	//	}
	//	else
		if (is_valid_cmd(shell->cmds->full_cmd[0], envp))
			cmd++;
		if (shell->cmds->next)
			shell->cmds = shell->cmds->next;
		else
			break ;
	}
	rewind_cmd(&shell->cmds, 1);
	error_msg(shell, shell->cmds, envp);
	if (cmd)
		exec_cmd(shell, shell->cmds->full_path, envp);
}
