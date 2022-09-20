/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:02:22 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/19 20:10:19 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	tokenizer_support_func(t_token **token, int i, int *j, char *line)
{
	if (line[i] == '"')
	{
		if (dquotes_func(token, i, j, line) == 1)
			return (1);
	}
	else if (line[i] == 39)
	{
		if (squotes_func(token, i, j, line) == 2)
			return (2);
	}
	else if (ft_isprint(line[i]))
		noquotes_func(token, i, j, line);
	else
		(*j)++;
	return (0);
}

t_token	*make_new_token(char *line, int i, int j)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->empty_cmd = 0;
	if (i == 0 || (i != 0 && line[i - 1] != 39 && line[i - 1] != '"'))
		new->value = ft_substr(line, i, j - 1);
	else
	{
		if (j == 0)
		{
			new->empty_cmd = 1;
			new->value = ft_strdup(" ");
		}
		else
			new->value = ft_substr(line, i, j);
	}
	new->type = WORD;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	add_new_token(t_token **token, char *line, int i, int j)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = make_new_token(line, i, j);
	tmp->next->prev = tmp;
}

void	free_token(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		*token = (*token)->next;
		if (tmp->value)
			free(tmp->value);
		if (tmp)
			free(tmp);
		tmp = *token;
	}
}

void	get_token_type(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
	{
		if (!ft_strncmp(tmp->value, "|", ft_strlen(tmp->value)))
			tmp->type = PIPE;
		else if (!ft_strncmp(tmp->value, "<", ft_strlen(tmp->value)))
			tmp->type = REDIR_IN;
		else if (!ft_strncmp(tmp->value, ">", ft_strlen(tmp->value)))
			tmp->type = REDIR_OUT;
		else if (!ft_strncmp(tmp->value, "<<", ft_strlen(tmp->value)))
			tmp->type = DREDIR_IN;
		else if (!ft_strncmp(tmp->value, ">>", ft_strlen(tmp->value)))
			tmp->type = DREDIR_OUT;
		else
		{
			if (tmp->prev != NULL && tmp->prev->type == DREDIR_IN)
				tmp->type = HERE_DOC;
			else
				tmp->type = WORD;
		}
		tmp = tmp->next;
	}
}
