#include "../../inc/minishell.h"

t_token	*make_new_token(char *line, int i, int j, int quotes)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->empty_cmd = 0;
	if (quotes == 1)
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
	new->quotes = quotes;
	return (new);
}

void	add_new_token(t_token **token, char *line, int i, int j, int quotes)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = make_new_token(line, i, j, quotes);
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
