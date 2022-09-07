/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:07:52 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/07 17:11:42 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
