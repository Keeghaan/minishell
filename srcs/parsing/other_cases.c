/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:41:57 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/19 16:20:07 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_symbol(char *token)
{
	if (*token == '|' || *token == '<' || *token == '>')
		return (1);
	return (0);
}

int	check_cmd(char *token, char **envp)
{
	int		j;
	char	*tmp;
	char	*path;
	char	**env;

	j = -1;
	env = get_env(envp);
	if (!env)
		return (-3);
	while (env[++j])
	{
		tmp = ft_strjoin(env[j], "/");
		if (!tmp)
			return (-1);
		path = ft_strjoin(tmp, token);
		if (!path)
			return (-2);
		free(tmp);
		if (access(path, F_OK | R_OK | X_OK) == 0)
			return (free(path), free_split(env), 1);
		free(path);
	}
	return (free_split(env), 0);
}

static int	check_file(char *token)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd > -1)
		return (close(fd), 1);
	if (!check_symbol(token))
		printf("%s: %s: %s\n", SH, token, strerror(errno));
	return (0);
}

int	which_case(t_token **token)
{
	t_token	*t;
	int		file;
	int		symbol;

	file = 0;
	t = *token;
	symbol = 0;
	while (t)
	{
		if (check_symbol(t->value))
			symbol++;
		else if (t->type != HERE_DOC)
		{
			if  (check_file(t->value))
			file++;
		}
		if (t->next)
			t = t->next;
		else
			break ;
	}
	if (!file)
		return (1);
	if (file)
		return (2);
	return (0);
}
