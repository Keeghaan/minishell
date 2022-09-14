/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:45:38 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/14 16:57:02 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	possibilities(t_shell *shell, char *action)
{
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
	get_next_dir(shell, action);
	if (access(shell->next_dir, F_OK | X_OK) != 0)
		return (printf("%s: %s: %s: %s\n", SH, "cd",
				action, strerror(errno)), 0);
	return (4);
}

int	cd_cmd(t_shell *shell, char *action)
{
	int	move;

	move = possibilities(shell, action);
	if (!move)
		return (1);
	if (move == 4)
	{
		if (chdir(shell->next_dir) != 0)
			return (3);
	}
	get_cwd(shell);
	printf("cd cmd cwd : %s\n", shell->cwd);
	return (0);
}
