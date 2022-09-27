/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:27:02 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/26 14:28:57 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_envp(t_envp *envp, t_cmd *cmd, t_shell *shell)
{
	t_envp	*tmp;

	(void)envp;
	if (cmd->full_cmd[1])
		return ;
	cmd->out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out < 0)
		return ;
	tmp = shell->envp;
	while (tmp && tmp->visible)
	{
		write(cmd->out, tmp->var, ft_strlen(tmp->var));
		write(cmd->out, "=", 1);
		write(cmd->out, tmp->values, ft_strlen(tmp->values));
		write(cmd->out, "\n", 1);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	close(cmd->out);
}
