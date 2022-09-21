/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:17:57 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/21 20:17:59 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	get_global_return(t_token **token)
{
	free((*token)->value);
	(*token)->value = ft_itoa(g_return);
}

void	expand_tmp(char **tmp, t_shell *shell, char *delimiter)
{
	t_envp	*envp;
	t_token	*token;
	char	*str;

	token = shell->token;
	while (ft_strncmp(token->value, delimiter, ft_strlen(token->value)))
		token = token->next;
	envp = shell->envp;
	if (token->quotes == 1)
	{
		str = *tmp;
		str = ft_substr(str, 1, ft_strlen(str));
		free(*tmp);
		*tmp = ft_strdup(str);
		free(str);
		while (envp)
		{
			if (!ft_strncmp(envp->var, *tmp, ft_strlen(envp->var)))
			{
				free(*tmp);
				*tmp = ft_strdup(envp->values);
			}
			envp = envp->next;
		}
	}	
}	
