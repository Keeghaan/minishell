/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 13:45:38 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/29 14:55:17 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	move_back(t_shell *shell, char *action)
{
	int	back;
	char	**tmp;
	int	j;
(void)shell;
	back = 0;
	j = 0;
	tmp = ft_split(action, '/');
	if (!tmp)
		return (1);
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
	int	back;

	if (ft_strnstr(action, "..", ft_strlen(action)))
	{
		back = move_back(shell, action);
		free(shell->prev_dir);
		get_prev_dir(shell, back);
		if (access(shell->prev_dir, F_OK | X_OK) != 0)
			return (printf("%s: %s: %s: %s\n", SH, "cd", shell->prev_dir, strerror(errno)), 0);
		return (1);
	}
	free(shell->next_dir);
	get_next_dir(shell, action);
	if (access(shell->next_dir, F_OK | X_OK) != 0)
		return (printf("%s: %s: %s: %s\n", SH, "cd", shell->next_dir, strerror(errno)), 0);
	return (2);
}

int	cd_cmd(t_shell *shell, char *action)
{
	int	move;

	move = possibilities(shell, action);
	if (move == 1)
	{
		if (chdir(shell->prev_dir) != 0)
			return (printf("%s\n", strerror(errno)), 2);
	}
	if (move == 2)
	{
		if (chdir(shell->next_dir) != 0)
			return (printf("%s\n", strerror(errno)), 3);
	}
	else
		return (free_shell(shell), 4);
	free(shell->next_dir);
	free(shell->prev_dir);
	get_cwd(shell);
	printf("cd %s\n%s\n%s\n", shell->cwd, shell->prev_dir, shell->next_dir); //
	return (0);
}
