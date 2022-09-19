/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:02:51 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/19 15:02:53 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	double_cmd_ter(t_token *t, int msg)
{
	int	dir;

	dir = is_a_dir(t->next->next->next->value);
	if (msg && dir == 3)
	{
		printf("%s: %s: %s\n", t->value,
			t->next->next->next->value, strerror(21));
		return (3);
	}
	else if (dir == 2 && t->next->next->next->next
		&& t->next->next->next->next->type == PIPE)
		return (5);
	else if (dir == 2 && !t->next->next->next->next)
		return (1);
	if (msg && !dir)
	{
		printf("%s: %s: %s\n", t->value,
			t->next->next->next->value, strerror(2));
		return (1);
	}
	return (1);
}

int	double_cmd_bis(t_token *t, int msg)
{
	if (t->next && t->next->type == REDIR_IN && t->next->next
		&& t->next->next->type == WORD && t->next->next->next
		&& t->next->next->next->type == WORD)
	{
		if (is_a_dir(t->value) == 3)
			return (printf("%s: %s: %s\n", SH, t->value, strerror(21)), 4);
		if (is_a_dir(t->value) == 2)
			return (4);
		if (t->next->next->next->empty_cmd)
		{
			if (msg)
				printf("%s: '': %s\n", t->value, strerror(2));
			return (1);
		}
		else
			return (double_cmd_ter(t, msg));
	}
	return (0);
}

int	double_cmd(t_token **tok, int msg)
{
	t_token	*t;

	t = *tok;
	while (t)
	{
		if (t->type == WORD)
		{
			if (double_cmd_bis(t, msg) > 1)
				return (2);
			else if (double_cmd_bis(t, 0))
				return (1);
		}
		if (t->next)
			t = t->next;
		else
			break ;
	}
	return (0);
}

void	rewind_cmd(t_cmd **cmd, int back)
{
	if (back)
	{
		while (*cmd)
		{
			if ((*cmd)->prev)
				*cmd = (*cmd)->prev;
			else
				break ;
		}
	}
	else
	{
		while (*cmd)
		{
			if ((*cmd)->next)
				*cmd = (*cmd)->next;
			else
				break ;
		}
	}
}

void	rewind_token(t_token **token, int back)
{
	if (back)
	{
		while (*token)
		{
			if ((*token)->prev)
				*token = (*token)->prev;
			else
				break ;
		}
	}
	else
	{
		while (*token)
		{
			if ((*token)->next)
				*token = (*token)->next;
			else
				break ;
		}
	}
}
