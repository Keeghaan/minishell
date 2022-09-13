/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cases.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 12:41:57 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/13 14:08:57 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	check_symbol(char *token)
{
	if (*token == '|' || *token == '<' || *token == '>')
		return (1);
	return (0);
}
/*
static int	check_cmd(char *token, char **envp)
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
		printf("shell env %s\n", env[j]);
		tmp = ft_strjoin(env[j], "/");
		if (!tmp)
			return (-1);
		path = ft_strjoin(tmp, token);
		if (!path)
			return (-2);
		free(tmp);
		if (access(path, F_OK | R_OK | X_OK) == 0)
			return (free(path), free_split(envp), 1);
		free(path);
	}
	return (free_split(envp), 0);
}*/

static int	check_file(char *token)
{
	int	fd;

	fd = open(token, O_RDONLY);
       	if (fd > -1)
		return (close(fd), 1);
	if (!check_symbol(token))
		printf("%s: %s: %s\n", SH, token, strerror(errno)); //verifier syntax
	return (close(fd), 0);
}

int	which_case(t_token **token, char **envp)
{
	(void)envp;
	t_token	*t;
//	int		cmd;
	int		file;
	int		symbol;

	t = *token;
//	cmd = 0;
	file = 0;
	symbol = 0;
	while (t)
	{
		printf("OTHERCASE.c %s token\n", t->value);///
		//if (check_cmd(t->value, envp))
	//		cmd++;
		if (check_file(t->value))
		{
			printf("othercase.c %s file is file\n", t->value);//
			file++;
		}
		else if (check_symbol(t->value))
		{
			printf("othercase.c symbol %s is symbol ? (verifier << >>)\n", t->value);//
			symbol++;
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
