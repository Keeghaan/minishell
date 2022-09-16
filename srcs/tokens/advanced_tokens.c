#include "../../inc/minishell.h"

int	ft_iscrochet(char *s, int i)
{
	if (ft_strlen(s) == 1)
		return (0);
	if (ft_strlen(s) >= 2)
	{
		if (s[i] == '<' || s[i] == '>')
		{
			if (s[i + 1] && i != 0 && s[i + 1] != s[i] && s[i - 1] != s[i])
				return (1);
			else if (i == 0 && s[i + 1] && s[i + 1] != s[i])
				return (1);
			else if (!s[i + 1] && i != 0 && s[i - 1] != s[i])
				return (1);
		}
		if (s[i] == '|')
			return (1);
	}
	return (0);
}

void	insert_token_list(t_token **token, char *value)
{
	t_token	*tmp;
	t_token	*new;

	tmp = *token;
	new = malloc(sizeof(t_token));
	new->value = ft_strdup(value);
	new->type = WORD;
	new->quotes = 1;
	if (tmp->next != NULL)
	{
		new->next = tmp->next;
		new->prev = tmp;
		tmp->next->prev = new;
		tmp->next = new;
	}
	if (tmp->next == NULL)
	{
		new->next = NULL;
		tmp->next = new;
		new->prev = tmp;
	}
}

void	str_separate(t_token **t, int i, int len)
{
	char	*s1;
	char	*s2;

	if (i == 0)
	{
		s1 = ft_substr((*t)->value, i, len);
		s2 = ft_substr((*t)->value, len, ft_strlen((*t)->value) + 1 - len);
	}
	else
	{
		s1 = ft_substr((*t)->value, 0, i);
		s2 = ft_substr((*t)->value, i, ft_strlen((*t)->value) - i);
	}
	free((*t)->value);
	(*t)->value = ft_strdup(s1);
	insert_token_list(t, s2);
	free(s1);
	free(s2);
}

void	tokenize_advanced(t_token **token)
{
	int	i;
	int	size;

	i = 0;
	while ((*token))
	{
		if ((*token)->quotes == 1)
		{
			while ((*token)->value[i])
			{
				size = ft_iscrochet((*token)->value, i);
				if (size)
				{
					str_separate(token, i, size);
					i = 0;
				}
				i++;
			}
		}
		if ((*token)->next == NULL)
			break ;
		*token = (*token)->next;
		i = 0;
	}
	while ((*token)->prev)
		*token = (*token)->prev;
	get_token_type(token);
}
