#include "../../inc/minishell.h"

int	double_quotes_tokens(t_token **token, int i, int *j, int k, char *line)
{
	*j = i;
	while (line[*j] && line[*j] != '"')
		(*j)++;
	if (!line[*j])
	{
		return (1);
	}	
	if (line[*j] == '"')
	{
		if (k == 0)
			*token = make_new_token(line, i, *j - i, 3);
		else
			add_new_token(token, line, i, *j - i, 3);
	}
	return (0);
}

int	single_quotes_tokens(t_token **token, int i, int *j, int k, char *line)
{
	*j = i;
	while (line[*j] && line[*j] != 39)
		(*j)++;
	if (!line[*j])
	{
		return (1);
	}	
	if (line[*j] == 39)
	{
		if (k == 0)
			*token = make_new_token(line, i, *j - i, 2);
		else
			add_new_token(token, line, i, *j - i, 2);
	}
	return (0);
}

void	no_quotes_tokens(t_token **token, int i, int *j, int k, char *line)
{
	*j = i;
	while (line[*j] && line[*j] != ' ' && line[*j] != '"' && line[*j] != 39)
		(*j)++;
	if (k == 0)
		*token = make_new_token(line, i, *j - i + 1, 1);
	else
		add_new_token(token, line, i, *j - i + 1, 1);
}

int	tokenizer(char *line, t_token **token, t_envp **env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
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
		if (line[i] == '"')
		{
			if (double_quotes_tokens(token, i + 1, &j, k, line))
				return (1);
			j++;
		}
		else if (line[i] == 39)
		{
			if (single_quotes_tokens(token, i + 1, &j, k, line))
				return (2);
			j++;
		}
		else if (ft_isprint(line[i]))
			no_quotes_tokens(token, i, &j, k, line);
		else
			j++;;
		i = j;	
		k++;
	}
	if ((*token)->value)
		expander(token, env);
	return (0);
}
