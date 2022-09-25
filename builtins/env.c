/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:27:02 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/23 11:53:15 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_envp(t_envp *envp, t_cmd *cmd)
{
	t_envp	*tmp;

	if (cmd->full_cmd[1])
		return ;
	tmp = envp;
	while (tmp)
	{
		//write(STDOUT_FILENO, tmp->var, ft_strlen(tmp->var));
		//write(STDOUT_FILENO, "=", 1);
		//write(STDOUT_FILENO, tmp->values, ft_strlen(tmp->values));
		//write(STDOUT_FILENO, "\n", 1);
		printf("%s", tmp->var);
		printf("=");
		printf("%s\n", tmp->values);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
}
