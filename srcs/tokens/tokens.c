/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 15:02:07 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/19 15:47:20 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	no_quotes_tokens_two(t_token **token, int i, int *j, char *line)
{
	t_token	*tmp;

	*j = i;
	while (line[*j] && line[*j] != ' ' && line[*j] != '"' && line[*j] != 39)
		(*j)++;
	add_new_token(token, line, i, *j - i + 1);
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->quotes = 1;
}

int	dquotes_func(t_token **token, int i, int *j, char *line)
{
	if (*token == NULL)
	{
		if (double_quotes_tokens_one(token, i + 1, j, line))
			return (1);
	}
	else
	{
		if (double_quotes_tokens_two(token, i + 1, j, line))
			return (1);
	}
	(*j)++;
	return (0);
}

int	squotes_func(t_token **token, int i, int *j, char *line)
{
	if (*token == NULL)
	{
		if (single_quotes_tokens_one(token, i + 1, j, line))
			return (2);
	}
	else
	{
		if (single_quotes_tokens_two(token, i + 1, j, line))
			return (2);
	}
	(*j)++;
	return (0);
}

void	noquotes_func(t_token **token, int i, int *j, char *line)
{
	if (*token == NULL)
		no_quotes_tokens_one(token, i, j, line);
	else
		no_quotes_tokens_two(token, i, j, line);
}

int	tokenizer(char *line, t_token **token, t_envp **env)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	*token = NULL;
	while (i < (int)ft_strlen(line))
	{
		while ((line[i] >= 9 && line[i] <= 13) || line[i] == ' ')
			i++;
		if (!line[i])
		{
			if (!(*token))
				return (0);
			else
				break ;
		}
		check = tokenizer_support_func(token, i, &j, line);
		if (check)
			return (check);
		i = j;
	}
	return (0);
}
