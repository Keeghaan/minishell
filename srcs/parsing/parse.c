/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:59 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/21 21:09:10 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

<<<<<<< HEAD
=======
char	*check_tokens(t_token **t)
{
	t_token	*tmp;
	int		i;

	tmp = *t;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE && i == 0)
			return (tmp->value);
		if (!tmp->next && tmp->type != WORD && tmp->type != HERE_DOC)
			return ("newline");
		if (((tmp->type == REDIR_IN || tmp->type == REDIR_OUT
					|| tmp->type == DREDIR_IN
					|| tmp->type == DREDIR_OUT)
				&& tmp->next) && (tmp->next->type != WORD
				&& tmp->next->type != HERE_DOC))
			return (tmp->next->value);
		i++;
		tmp = tmp->next;
	}	
	return (NULL);
}

>>>>>>> norminette
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

void	check_cmd_found(t_token *token, t_shell *shell)
{
	t_token	*tmp;
	int		cases;

	tmp = token;
	if (tmp->prev)
		tmp = tmp->prev;
	while (tmp->type != PIPE)
	{
		if (tmp->prev)
			tmp = tmp->prev;
		else
			break ;
	}
	if (tmp->type == PIPE)
		tmp = tmp->next;
	cases = which_case(&tmp, shell);
	if (cases == 1)
		shell->ret = 1;
}

static void	no_cmd_func(t_shell *shell, t_token *tmp, t_cmd **cmd)
{
	check_cmd_found(tmp, shell);
	if (*cmd)
		add_null_cmd(cmd);
	else
		*cmd = make_new_cmd_null();
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
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

void	get_cmds_bis(t_token *tmp, t_shell *shell, t_cmd **cmd)
{
	int	i;

	i = 0;
	shell->cmd_found = 0;
	while (tmp)
	{
		if (tmp->type == WORD && !no_redir(tmp))
			get_cmds_bis_bis(&tmp, cmd, shell, i);
		if ((tmp->type == PIPE || !tmp->next) && shell->cmd_found == 0)
			no_cmd_func(shell, tmp, cmd);
		if ((tmp && !tmp->next) || !tmp)
			break ;
		if (tmp->type == PIPE)
			shell->cmd_found = 0;
		tmp = tmp->next;
		i++;
	}
}

int	get_cmds(t_token **t, t_cmd **cmd, t_shell *shell)
{
	t_token	*tmp;

	tmp = *t;
	get_cmds_bis(tmp, shell, cmd);
	if (*cmd)
		return (1);
	return (0);
}

int	parse(t_token **token, t_shell *shell)
{
	char	*check;

	check = check_tokens(token);
	if (check)
	{		
		ft_printf("minishell: syntax error near unexpected token `%s'\n", check);
		shell->ret = 2;
		return (-1);
	}
	shell->ret = 0;
	if (get_cmds(token, &shell->cmds, shell))
		return (1);
	return (0);
}
