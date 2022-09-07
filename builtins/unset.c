/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:30:24 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/07 14:33:58 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_envp_bis(t_envp *tmp)
{
	t_envp	*tmp2;
	t_envp	*tmp3;

	tmp3 = tmp;
	while (tmp3->next != NULL)
	{
		if (tmp3->next->var == var)
		{
			tmp2 = tmp3->next;
			tmp3->next = tmp3->next->next;
			free(tmp2);
			break ;
		}
		else
		tmp3 = tmp3->next;
	}
}

void	unset_envp(t_shell *shell, char *unset)
{
	t_envp	*tmp;
	t_envp	*tmp2;

	tmp = shell->envp;
	if (tmp->var == unset)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
	else
		unset_envp(tmp);
}
