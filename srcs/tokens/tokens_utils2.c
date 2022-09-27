/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:03:26 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/19 15:21:30 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	double_quotes_tokens_one(t_token **token, int i, int *j, char *line)
{
	t_token	*tmp;

	*j = i;
	while (line[*j] && line[*j] != '"')
	{
		(*j)++;
	}
	if (!line[*j])
	{
		return (1);
	}	
	if (line[*j] == '"')
		*token = make_new_token(line, i, *j - i);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->quotes = 3;
	return (0);
}

int	double_quotes_tokens_two(t_token **token, int i, int *j, char *line)
{
	t_token	*tmp;

	*j = i;
	while (line[*j] && line[*j] != '"')
	{
		(*j)++;
	}
	if (!line[*j])
	{
		return (1);
	}	
	if (line[*j] == '"')
		add_new_token(token, line, i, *j - i);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->quotes = 3;
	return (0);
}

int	single_quotes_tokens_one(t_token **token, int i, int *j, char *line)
{
	t_token	*tmp;

	*j = i;
	while (line[*j] && line[*j] != 39)
		(*j)++;
	if (!line[*j])
	{
		return (1);
	}	
	if (line[*j] == 39)
			*token = make_new_token(line, i, *j - i);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->quotes = 2;
	return (0);
}

int	single_quotes_tokens_two(t_token **token, int i, int *j, char *line)
{
	t_token	*tmp;

	*j = i;
	while (line[*j] && line[*j] != 39)
		(*j)++;
	if (!line[*j])
	{
		return (1);
	}	
	if (line[*j] == 39)
		add_new_token(token, line, i, *j - i);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->quotes = 2;
	return (0);
}

void	no_quotes_tokens_one(t_token **token, int i, int *j, char *line)
{
	t_token	*tmp;

	*j = i;
	while (line[*j] && line[*j] != ' ' && line[*j] != '"' && line[*j] != 39)
		(*j)++;
	*token = make_new_token(line, i, *j - i + 1);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->quotes = 1;
}
