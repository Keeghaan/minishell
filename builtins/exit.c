/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:34:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/14 10:30:45 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	get_nb_tokens(t_shell *shell)
{
	t_token	*token;
	int	i;

	i = 1;
	token = shell->token;
	while (token)
	{
		if (token->next)
			token = token->next;
		else
			break ;
		i++;
	}
	return (i);
}

static int	is_digit(t_shell *shell)
{
	t_token	*token;
	int	i;

	token = shell->token;
	token = token->next;
	i = 0;
	if (token->value[i] == '+' || token->value[i] == '-')
		i++;
	if (i && !token->value[i])
		return (0); // faut faire gaffe parfois ca bug O___O (exit:command not found mais je comprends pas et c'est pas tout le tempss)
	while (token->value[i])
	{
		if (!ft_isdigit(token->value[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_exit(t_shell *shell, char *buf)
{
	char	**split;
	int	n;
	int	is_numeric;

	split = ft_split(buf, ' ');
	n = get_nb_tokens(shell);
	is_numeric = is_digit(shell);
	ft_putendl_fd("exit", 1);
	if (!split)
		return ;
	//shell->is_running = 0;
	if (!is_numeric)
		printf("minishell: %s: %s: numeric argument required\n", split[0], split[1]);
	else if (is_numeric && n > 2)
	{
		printf("minishell: %s: too many arguments\n", split[0]);
		free_split(split);
		return ;
	}
	else
		;
	free_split(split);
	exit(0);
}
