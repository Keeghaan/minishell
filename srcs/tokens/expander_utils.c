/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:00:28 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/19 10:04:54 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	support_expander_bis(t_token **token, char *value, t_envp **env, int *i)
{
	char	*check;

	check = expand_env_var(value, env, *i + 1);
	final_expansion(token, *i, check);
	if (check)
		free(check);
	*i = 0;
}
