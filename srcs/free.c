/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:42:41 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/16 13:01:05 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_exit(t_shell *shell)
{
	free_token(&shell->token);
	free_envp(&shell->envp);
	free_split(shell->env);
	exit(0);
}
