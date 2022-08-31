/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 17:59:48 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/29 18:05:50 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	arg_error(t_shell *shell)
{
	char **split;
	int		j;

	j = -1;
	split = ft_split(shell->buf, ' ');
	if (!split)
		return (1);
	while (split[++j])
	{
		if (!strncmp(split[0], "cd", ft_strlen(split[0])))
		{
			j++;
			if (split[j + 1])
				return (printf("%s: too many arguments\n", split[0]), 2);
		}
	}
	return (0);
}
