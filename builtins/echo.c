/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 14:01:43 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/23 14:26:00 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(char **cmd, int active)
{
	int	opt;
	int	i;

	i = 0;
	opt = 1;
	if (!ft_strncmp2(cmd[1], "-n", ft_strlen(cmd[1])))
	{
		while (cmd[1][i])
		{
			if (!(cmd[1][i] == '-' || cmd[1][i] == 'n'))
				opt = 0;
			i++;
		}
	}
	else
		opt = 0;
	if (active)
	{
		if (opt && cmd[2])
			ft_printf("%s", cmd[2]);
		else if (!opt && cmd[1])
			printf("%s\n", cmd[1]);
		else if (!opt && !cmd[1])
			printf("\n");
	}
}
