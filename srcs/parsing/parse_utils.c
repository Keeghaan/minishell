/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:16:27 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/22 12:20:00 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	get_cmds_bis(t_token *tmp, t_shell *shell, t_cmd **cmd)
{
	int	i;

	i = 0;
	shell->cmd_found = 0;
	while (tmp)
	{
		if (tmp->type == WORD && !no_redir(tmp))
			get_cmds_bis_bis(&tmp, cmd, shell, i);
		if ((tmp->type == PIPE || !tmp->next) && shell->cmd_found == 0)
		{
			if (no_cmd_func(shell, tmp, cmd) == 130)
				return (130);
		}
		if ((tmp && !tmp->next) || !tmp)
			break ;
		if (tmp->type == PIPE)
			shell->cmd_found = 0;
		tmp = tmp->next;
		i++;
	}
	return (0);
}

void	get_cmds_bis_bis(t_token **tmp, t_cmd **cmd, t_shell *shell, int i)
{
	if (i > 0 && (*tmp)->prev && (*tmp)->prev->type != REDIR_IN
		&& (*tmp)->prev->type != REDIR_OUT
		&& (*tmp)->prev->type != DREDIR_OUT)
	{
		if (*cmd)
			add_new_cmd(cmd, tmp, shell);
		else
			*cmd = make_new_cmd(tmp, shell);
	}
	else
		get_cmds_ter(tmp, i, shell, cmd);
}

void	get_cmds_ter(t_token **tmp, int i, t_shell *shell, t_cmd **cmd)
{
	if (i == 0 && (*tmp)->next && ((*tmp)->next->type == WORD
			|| (*tmp)->next->type == REDIR_IN
			|| (*tmp)->next->type == PIPE))
			*cmd = make_new_cmd(tmp, shell);
	else if ((*tmp)->prev && (*tmp)->prev->type == WORD && (*tmp)->prev->prev
		&& (*tmp)->prev->prev->type == REDIR_IN
		&& (*tmp)->prev->prev->prev && (*tmp)->prev->prev->prev->type == WORD
		&& (*tmp)->next && (*tmp)->next->type == PIPE)
	{
		if (!(*tmp)->next)
			return ;
		*tmp = (*tmp)->next;
	}
	else if (i == 0 && (*tmp)->next && (*tmp)->next->type == DREDIR_IN)
		*cmd = make_new_cmd(tmp, shell);
	else if (i == 0 && (*tmp)->next == NULL)
		*cmd = make_new_cmd(tmp, shell);
}

int	no_cmd_func(t_shell *shell, t_token *tmp, t_cmd **cmd)
{
	if (check_cmd_found(tmp, shell) == 130)
		return (130);
	if (*cmd)
		add_null_cmd(cmd);
	else
		*cmd = make_new_cmd_null();
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	return (0);
}

void	get_global_return(t_token **token)
{
	free((*token)->value);
	(*token)->value = ft_itoa(g_return);
}
