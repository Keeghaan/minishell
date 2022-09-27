/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:26:39 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/22 12:46:32 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset_envp_bis(t_envp *tmp, char *unset)
{
	t_envp	*tmp2;
	t_envp	*tmp3;

	tmp3 = tmp;
	while (tmp3->next != NULL)
	{
		if (!ft_strncmp(tmp3->next->var, unset, ft_strlen(tmp3->next->var)))
		{
			tmp2 = tmp3->next;
			tmp3->next = tmp3->next->next;
			free(tmp2->var);
			free(tmp2->values);
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
	if (!ft_strncmp(tmp->var, unset, ft_strlen(tmp->var)))
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2->var);
		free(tmp2->values);
		free(tmp2);
	}
	else
		unset_envp_bis(tmp, unset);
}
