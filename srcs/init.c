/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:06:36 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/29 17:49:16 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	init_shell(t_shell *shell, char *buf)
{	
	int	j;
	int	k;
	char	**split;

	j = -1;
	shell->builtins = malloc(sizeof(char *) * 9);
	if (!shell->builtins)
		return (1);
	shell->builtins[0] = "cd";
	shell->builtins[1] = "echo";
	shell->builtins[2] = "echo -n";
	shell->builtins[3] = "unset";
	shell->builtins[4] = "pwd";
	shell->builtins[5] = "exit";
	shell->builtins[6] = "env";
	shell->builtins[7] = "export";
	shell->buf = ft_strdup(buf);
	if (!shell->buf)
		return (1);
	split = ft_split(buf, ' ');
	if (!split)
		return (free(shell->buf), 2);
	while (split[++j])
	{
		k = -1;
		while (shell->builtins[++k])
		{
			if (!ft_strncmp(split[j], shell->builtins[k], ft_strlen(split[j])))
				return (printf("%s\n", split[j]), 1);
		}
	}
	return (0);
}
