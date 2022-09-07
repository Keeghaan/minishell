/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:34:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/07 14:34:36 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_exit(t_shell *shell, char *buf)
{
	char	**split;

	split = ft_split(buf, ' ');
	if (!split)
		return ;
	shell->is_running = 0;
	ft_putendl_fd("exit", 1);
	printf("minishell: %s: %s: numeric argument required\n", split[0], split[1]);
	free_split(split);
	exit(0);
}
