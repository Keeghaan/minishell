/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:17:57 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/21 20:17:59 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_global_return(t_token **token)
{
	free((*token)->value);
	(*token)->value = ft_itoa(g_return);
}

void	expand_tmp(char **tmp, t_shell *shell, char *delimiter)
{
	t_envp	*envp;
	t_token	*token;
	char	*str;

	token = shell->token;
	while (ft_strncmp(token->value, delimiter, ft_strlen(token->value)))
		token = token->next;
	envp = shell->envp;
	if (token->quotes == 1)
	{
		str = *tmp;
		str = ft_substr(str, 1, ft_strlen(str));
		free(*tmp);
		*tmp = ft_strdup(str);
		free(str);
		while (envp)
		{
			if (!ft_strncmp(envp->var, *tmp, ft_strlen(envp->var)))
			{
				free(*tmp);
				*tmp = ft_strdup(envp->values);
			}
			envp = envp->next;
		}
	}	
}

void	get_infile(t_token **tmp, t_cmd **new)
{
	t_token	*token;

	token = *tmp;
	if (!(*tmp)->prev && (*tmp)->next && (*tmp)->next->next
		&& (*tmp)->next->next->type == PIPE && (*tmp)->next->type == WORD)
		(*new)->infile = (*tmp)->next->value;
	else if (((*tmp)->prev == NULL || (*tmp)->prev->type == PIPE)
		&& (*tmp)->next && (*tmp)->next->type != REDIR_IN)
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->prev == NULL && ((*tmp)->next == NULL
			|| (*tmp)->next->type == PIPE))
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->prev && (*tmp)->prev->type == PIPE)
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->next && (*tmp)->next->type
		== REDIR_IN && (*tmp)->next->next)
	{
		token = token->next->next;
		while (token->next && token->next->next && token->next->type == WORD
			&& token->next->next->type == PIPE)
			token = token->next;
		(*new)->infile = token->value;
	}		
	else if ((*tmp)->prev->prev && (*tmp)->prev->prev->type == REDIR_IN
		&& !(*tmp)->prev->prev->prev)
		(*new)->infile = (*tmp)->prev->value;
	else
		(*new)->infile = "/dev/stdin";
}

void	get_outfile(t_token **tmp, t_cmd **new)
{	
	if ((*tmp)->type == REDIR_OUT)
		(*new)->outfile = (*tmp)->next->value;
	else if ((*tmp)->prev == NULL && (*tmp)->next == NULL)
		(*new)->outfile = "/dev/stdout";
	else if ((*tmp)->type == PIPE)
		(*new)->outfile = "/dev/stdout";
	else if ((*tmp)->type == DREDIR_IN)
	{
		if ((*tmp)->next->next && (*tmp)->next->next->type == PIPE)
			(*new)->outfile = "/dev/stdout";
		else if ((*tmp)->next->next && (*tmp)->next->next->next
			&& (*tmp)->next->next->type == REDIR_OUT)
			(*new)->outfile = (*tmp)->next->next->next->value;
		else
			(*new)->outfile = "/dev/stdout";
	}
	else
		(*new)->outfile = "/dev/stdout";
	(*new)->redir = 1;
	if ((*tmp)->type == DREDIR_OUT)
	{
		(*new)->outfile = (*tmp)->next->value;
		(*new)->redir = 2;
	}
}
