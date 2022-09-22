/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:21:12 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/22 11:14:31 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	support_get_infile(t_token *token, t_cmd **new)
{
	token = token->next->next;
	while (token->next && token->next->next && token->next->type == WORD
		&& token->next->next->type == PIPE)
		token = token->next;
	(*new)->infile = token->value;
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
	else if (((*tmp)->prev == NULL || (*tmp)->prev->type == PIPE)
		&& (*tmp)->next && (*tmp)->next->type == REDIR_IN)
		(*new)->infile = (*tmp)->next->next->value;
	else if ((*tmp)->prev == NULL && ((*tmp)->next == NULL
			|| (*tmp)->next->type == PIPE))
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->prev && (*tmp)->prev->type == PIPE)
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->next && (*tmp)->next->type
		== REDIR_IN && (*tmp)->next->next)
		support_get_infile(token, new);
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
					|| tmp->type == DREDIR_IN || tmp->type == DREDIR_OUT
					/*|| tmp->type == PIPE*/) && tmp->next)
			&& (tmp->next->type != WORD && tmp->next->type != HERE_DOC))
			return (tmp->next->value);
		i++;
		tmp = tmp->next;
	}	
	return (NULL);
}
