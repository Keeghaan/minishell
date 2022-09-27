/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:01:43 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/26 19:10:34 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_echo(t_cmd *cmd, int i, int opt)
{
	cmd->out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!cmd->out)
		return ;
	if (!cmd->full_cmd[1])
	{
		write(cmd->out, "\n", 1);
		return ;
	}
	if (cmd->full_cmd[i])
	{
		while (cmd->full_cmd[i])
		{
			if (cmd->full_cmd[i + 1])
			{
				write(cmd->out, cmd->full_cmd[i], ft_strlen(cmd->full_cmd[i]));
				write(cmd->out, " ", 1);
			}
			else
				write(cmd->out, cmd->full_cmd[i], ft_strlen(cmd->full_cmd[i]));
			i++;
		}
		if (!opt)
			write(cmd->out, "\n", 1);
	}
	close(cmd->out);
}

static void	echo_active(int opt, t_cmd *cmd)
{
	if (opt && cmd->full_cmd[1] && cmd->full_cmd[2])
		print_echo(cmd, 2, 1);
	else if (!opt && cmd->full_cmd[1])
		print_echo(cmd, 1, 0);
	else if (!cmd->full_cmd[1])
		printf("\n");
}

void	echo_cmd(t_cmd *cmd, int active)
{
	int	opt;
	int	i;

	i = 0;
	opt = 0;
	if (!ft_strncmp2(cmd->full_cmd[1], "-n", 2))
	{
		if (cmd->full_cmd[1][0] == '-')
			opt = 1;
		while (cmd->full_cmd[1][++i])
		{
			if (cmd->full_cmd[1][i] != 'n')
				opt = 0;
		}
	}
	if (active && cmd->full_cmd[0])
		echo_active(opt, cmd);
}
