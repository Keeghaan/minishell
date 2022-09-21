/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:26:52 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/21 21:26:53 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_var(char *argv)
{
	int		i;
	char	*var;

	i = 0;
	while (argv[i] != '=')
		i++;
	var = ft_substr(argv, 0, i);
	return (var);
}

char	*get_values(char *argv, t_shell *shell)
{
	int		i;
	int		j;
	char	*values;

	i = 0;
	j = 0;
	while (argv[i] != '=')
		i++;
	i++;
	if (!argv[i] && shell->token->next->next
		&& (shell->token->next->next->quotes == 2
			|| shell->token->next->next->quotes == 3))
		values = ft_strdup(shell->token->next->next->value);
	else
		values = ft_substr(argv, i, ft_strlen(argv));
	return (values);
}

void	fake_export(char *cmd, t_shell *shell)
{
	t_envp	*new;
	int		check;

	check = check_export(cmd, shell);
	if (!check)
	{
		new = make_exported(cmd, shell);
		add_exported(&shell->envp, new);
	}
}
