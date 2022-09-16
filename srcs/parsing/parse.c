/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:42:59 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/16 18:43:03 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//returns NULL if it worked and the value of the token if error

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
		if (!tmp->next && tmp->type != WORD)
			return ("newline");
		if ((tmp->type == REDIR_IN || tmp->type == REDIR_OUT
				|| tmp->type == DREDIR_IN || tmp->type == DREDIR_OUT
				|| tmp->type == PIPE) && tmp->next && tmp->next->type
			!= WORD && tmp->next->type != HERE_DOC)
			return (tmp->next->value);
		i++;
		tmp = tmp->next;
	}	
	return (NULL);
}

int	get_cmds(t_token **t, t_cmd **cmd, t_shell *shell)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = *t;
	while (tmp)
	{
		if (tmp->type == WORD)
		{
			if (i == 0 && tmp->next && (tmp->next->type == WORD
					|| tmp->next->type == REDIR_IN
					|| tmp->next->type == PIPE))
				*cmd = make_new_cmd(&tmp, shell);
			else if (tmp->prev->prev && tmp->prev->prev->type == REDIR_IN
				&& tmp->prev->prev->prev && tmp->prev->prev->prev->type == WORD
				&& tmp->next && tmp->next->type == PIPE)
			{
				if (tmp->next)
					tmp = tmp->next;
				else
					break ;
			}
			else if ( i == 0 && tmp->next && tmp->next->type == DREDIR_IN)
				*cmd = make_new_cmd(&tmp, shell);
			else if (i > 0 && tmp->prev && tmp->prev->type != REDIR_IN && tmp->prev->type != REDIR_OUT
					&& tmp->prev->type != DREDIR_OUT) //une commande ne peut jamais suivre une redirection
			{
				if (*cmd)
					add_new_cmd(cmd, &tmp, shell);
				else
					*cmd = make_new_cmd(&tmp, shell);
			}
			else if (i == 0 && tmp->next == NULL)
				*cmd = make_new_cmd(&tmp, shell);
		}
		if (tmp && tmp->next)
			tmp = tmp->next;
		else
			break ;
		i++;
	}
	if (*cmd)
		return (1);
	return (0);
}

//will return 0 if all went well and 1 if an error occured

int	parse(t_token **token, t_shell *shell)
{
	char	*check;

	check = check_tokens(token);
	if (check)
	{		
		ft_printf("minishell: syntax error near unexpected token `%s'\n", check);
		g_return = 2;
		return (0);
	}
	if (get_cmds(token, &shell->cmds, shell))
		return (1);
	return (0);
}
