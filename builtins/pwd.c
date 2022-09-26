/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:59:43 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/26 10:24:08 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(int active, t_shell *shell)
{
//	char	cwd[254];

//	getcwd(cwd, sizeof(cwd));
	if (active)
		printf("%s\n", shell->cwd);
}
