#include "../../inc/minishell.h"

// Expander will give environment variables $SOMETHING their corresponding values

char	*expand_env_var(char *val, t_envp **env, int i)
{
	t_envp	*tmp;
	char	*new_val;
	char	*rest;

	new_val = ft_substr(val, i, ft_strlen(val) - i);
	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->var, new_val, ft_strlen(tmp->var)))
		{			
			i += ft_strlen(tmp->var);
			if (!ft_isalnum(val[i]) && val[i] != '_')
			{
				rest = ft_substr(val, i, ft_strlen(val) - i);
				free(new_val);
				new_val = ft_strjoin(tmp->values, rest);
				return (free(rest), new_val);
			}
		}
		tmp = tmp->next;
	}
	return (free(new_val), NULL);
}

void	final_expansion(t_token **token, int i, char *val)
{
	char *start;

	if (i == 0)
	{
		free((*token)->value);
		if (val)
			(*token)->value = ft_strdup(val);
		else
			(*token)->value = ft_strdup("");
	}
	if (i > 0)
	{
		start = ft_substr((*token)->value, 0, i);
		free((*token)->value);
		if (val)
			(*token)->value = ft_strjoin(start, val);
		else
			(*token)->value = ft_strdup(start);
		free(start);
	}
}

void	handle_home(t_token **token, char *user)  // ~/something
{
	char	*home;
	char	*rest;
	char	*final1;
	char	*final2;

	home = "/home/";
	rest = ft_substr((*token)->value, 1, ft_strlen((*token)->value) - 1);
	final1 = ft_strjoin(home, user);
	final2 = ft_strjoin(final1, rest);
	free(rest);
	free((*token)->value);
	(*token)->value = ft_strdup(final2);
	free(final1);
	free(final2);
	free(user);
}

void	get_global_return(t_token **token)
{
	free((*token)->value);
	(*token)->value = ft_itoa(g_return);
	//printf("%s\n", (*token)->value);
}

void	support_expander(t_token **token, t_envp **env)
{
	char	*check;
	int	i;

	i = 0;
	while ((*token)->value[i])
	{
		if ((*token)->value[i] == '$')
		{
			if ((*token)->value[i + 1] == '?' && ft_strlen((*token)->value) == 2)
				get_global_return(token);
			else
			{
				check = expand_env_var((*token)->value, env, i + 1);
				final_expansion(token, i, check);
				if (check)
					free(check);
				i = 0;
			}
		}
		if (i == 0 && (*token)->value[i] == '~')
		{
			check = expand_env_var("USER", env, i);
			handle_home(token, check);
		}
		i++;
	}
}

void	expander(t_token **token, t_envp **env)
{
	while (*token)
	{
		if ((*token)->quotes == 1 || (*token)->quotes == 3)
			support_expander(token, env);
		if ((*token)->next == NULL)
				break ;
		*token = (*token)->next;
	}
	while (*token)
	{
		if ((*token)->prev == NULL)
			break ;
		*token = (*token)->prev;
	}
	tokenize_advanced(token);
}
