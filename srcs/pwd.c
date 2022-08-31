/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 13:34:17 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/29 14:55:37 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*pwd_cmd(t_shell *shell)
{
	getcwd(shell->cwd, sizeof(shell->cwd));
	if (errno)
		return (NULL);
	get_cwd(shell);
	return (shell->cwd);
}
