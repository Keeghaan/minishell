/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 13:17:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/06 14:12:19 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

//Est ce une variable d'environnement ??
int	is_env_var(t_envp *envp, char *var)
{
	while (envp)
	{
		if (!ft_strncmp(envp->var, var, ft_strlen(var))
			&& ft_strlen(var) == ft_strlen(envp->var))
			return (1);
		if (envp->next)
			envp = envp->next;
		else
			break ;
	}
	return (0);
}

//est ce une option ? (en vrai on peut juste verifier qu'il y ai un tiret ("-") donc a optimiser;
int	is_option(char *option)
{
	printf("option %c%c\n", option[0], option[1]);
	if ((option[0] == '-' && ft_strlen(option) > 1)
		|| (option[0] == '-' && option[1] == '-' && ft_strlen(option) > 3))
		return (1); //a voir comment ca fait avec des options inexistantes
	return (0);
}

int	is_valid_cmd(char *cmd, char **envp)
{
	int		j;
	char	**en;
	char	*tmp;
	char	*path;

	j = 0;
	while (cmd[j])
	{
		if (cmd[j++] == '.')
			return (0);
	}
	if (!check_path_cmd2(cmd))
	{
		path = ft_strdup(cmd);
		if (access(path, R_OK | X_OK) == 0)
			return (1);
		return (free(path), 0);
	}
	else
	{
		en = get_env(envp);
		while (en[j])
		{
			tmp = ft_strjoin(en[j], "/");//a proteger
			path = ft_strjoin(tmp, cmd);//a protger
			free(tmp);
			if (access(path, R_OK | X_OK) == 0)
				return (free(path), free_split(en), 1);
			free(path);
			j++;
		}
		free_split(en);
	}
	return (0);
}
