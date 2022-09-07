/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:45:38 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/07 15:45:57 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	move_back(char *action)
{
	int		back;
	int		j;
	char	**tmp;

	back = 0;
	j = 0;
	tmp = ft_split(action, '/');
	if (!tmp)
	{
		back++;
		return (1);
	}
	while (tmp[j])
	{
		if (ft_strnstr(tmp[j], "..", ft_strlen(action)))
			back++;
		free(tmp[j]);
		j++;
	}
	free(tmp);
	return (back);
}

int	possibilities(t_shell *shell, char *action)
{
	int		back;
	char	*user;
	char	*home;

	if (!action)
	{
		user = expand_env_var("USER", &shell->envp, 0);
		home = ft_strjoin("/mnt/nfs/homes/", user);
		if (!home)
			return (0);
		if (chdir(home) != 0)
			return (0);
		return (free(home), 2);
	}	
	if ((ft_strlen(action) == 2 && ft_strnstr(action, "./", 2))
		|| (ft_strlen(action) == 1 && *action == '.'))
		return (1);
	if (ft_strnstr(action, "..", ft_strlen(action)))
	{
		back = move_back(action);
		get_prev_dir(shell, back);
		if (access(shell->prev_dir, F_OK | X_OK) != 0)
			return (printf("%s: %s: %s: %s\n", SH, "cd",
					shell->prev_dir, strerror(errno)),
					free(shell->prev_dir), 0);
		return (3);
	}
	get_next_dir(shell, action);
	if (access(shell->next_dir, F_OK | X_OK) != 0)
		return (printf("%s: %s: %s: %s\n", SH, "cd",
				shell->next_dir, strerror(errno)), 0);
	return (4);
}

int	cd_cmd(t_shell *shell, char *action)
{
	int	move;

	move = possibilities(shell, action);
	if (!move)
		return (1);
	if (move == 3)
	{
		if (chdir(shell->prev_dir) != 0)
			return (2);
	}
	if (move == 4)
	{
		if (chdir(shell->next_dir) != 0)
			return (3);
	}
	get_cwd(shell);
	printf("cd cmd cwd : %s\n", shell->cwd);
	return (0);
}
