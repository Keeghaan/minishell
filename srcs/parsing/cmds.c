/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 12:40:36 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/26 15:40:36 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	add_new_cmd(t_cmd **cmd, t_token **tmp, t_shell *shell)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = *cmd;
	while (tmp_cmd->next)
		tmp_cmd = tmp_cmd->next;
	tmp_cmd->next = make_new_cmd(tmp, shell);
	tmp_cmd->next->prev = tmp_cmd;
}

t_cmd	*make_new_cmd_bis(t_shell *shell, t_token **tmp, t_cmd *new, int count)
{
	int	i;

	i = 0;
	if ((*tmp)->empty_cmd)
		new->empty = 1;
	new->full_cmd = (char **)malloc(sizeof(char *) * count);
	if (!new->full_cmd)
		return (NULL);
	new->quotes = (*tmp)->quotes;
	while (*tmp && (*tmp)->type == WORD)
	{
		new->full_cmd[i] = ft_strdup(((*tmp)->value));
		if (!new->full_cmd[i])
			return (free_split(new->full_cmd), NULL);
		i++;
		if (!(*tmp)->next)
			break ;
		*tmp = (*tmp)->next;
	}
	get_outfile(tmp, &new);
	new->full_cmd[i] = NULL;
	new->full_path = get_full_path(shell, new->full_cmd[0]);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_cmd	*make_new_cmd(t_token **tmp, t_shell *shell)
{
	t_cmd	*new;
	t_token	*curr;
	int		count;

	count = 0;
	curr = *tmp;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	shell->cmd_found = 1;
	new->redir = 0;
	new->empty = 0;
	if ((*tmp)->next && (*tmp)->next->type == DREDIR_IN)
		get_here_doc(tmp, &new, shell, 0);
	else
		get_infile(tmp, &new);
	while (curr)
	{
		count += ft_strlen(curr->value) + 1;
		if (curr->next)
			curr = curr->next;
		else
			break ;
	}
	return (make_new_cmd_bis(shell, tmp, new, count));
}

t_cmd	*make_new_cmd_null(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->empty = 0;
	new->infile = "/dev/stdin";
	new->outfile = "/dev/stdout";
	new->redir = 1;
	new->empty = 0;
	new->full_cmd = malloc(sizeof(char *));
	new->full_cmd[0] = ft_strdup("");
	new->full_path = NULL;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_null_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = make_new_cmd_null();
	tmp->next->prev = tmp;
}
