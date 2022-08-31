/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 17:14:11 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/08/30 17:21:07 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	process(t_shell *shell, char **envp)
{
	printf("process.c\n");
	printf("?\n");
	execve(shell->cmds->full_path, shell->cmds->full_cmd, envp);
	close_pipes(shell);
	close_files(shell->cmds);
	printf("execve failed\n"); //
}
