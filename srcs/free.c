/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:42:41 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/14 11:58:28 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_shell(t_shell *shell) //pas sur que ce soit utile
{
	if (shell->next_dir )
		free(shell->next_dir);
	if (shell->prev_dir)
		free(shell->prev_dir);
	free_split(shell->env);
}

void	free_exit(t_shell *shell)
{
	free_token(&shell->token);
	free_envp(&shell->envp);
	free_split(shell->env);
	exit(0);
}
