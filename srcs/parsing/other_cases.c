/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:41:57 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/21 20:00:39 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_symbol(char *token)
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

int	check_file(char *token, int msg)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd > -1)
		return (close(fd), 1);
	if (!check_symbol(token) && msg)
		printf("%s: %s: %s\n", SH, token, strerror(errno));
	return (0);
}

void	create_file(t_token **t)
{
	int	fd;

	fd = -2;
	if ((*t)->prev->type == REDIR_OUT)
		fd = open((*t)->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*t)->prev->type == DREDIR_OUT)
		fd = open ((*t)->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		printf("minishell: %s: %s\n", (*t)->value, strerror(errno));
	if (fd)
		close(fd);
}

int	which_case(t_token **token, t_shell *shell)
{
	t_token	*t;
	int		file;
	int		symbol;

	file = 0;
	t = *token;
	symbol = 0;
	while (t && t->type != PIPE)
	{
		which_cases_bis(t, &symbol, &file);
		if (t->type == DREDIR_IN)
		{
			if (get_here_doc(&t, NULL, shell, 1) == 130)
				break ;
		}
		if (!t->next)
			break ;
		t = t->next;
	}
	if (!file)
		return (1);
	if (file)
		return (2);
	return (0);
}
