/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:59:43 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/23 14:00:16 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pwd(int active)
{
	char	cwd[254];

	getcwd(cwd, sizeof(cwd));
	if (active)
		printf("%s\n", cwd);
}