/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:34:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/26 16:07:49 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_digit(t_shell *shell)
{
	t_token	*token;
	int		i;

	token = shell->token;
	token = token->next;
	i = 0;
	if (token->value[i] == '+' || token->value[i] == '-')
		i++;
	if (i && !token->value[i])
		return (0);
	while (token->value[i])
	{
		if (!ft_isdigit(token->value[i]))
			return (0);
		i++;
	}
	return (ft_atoi(token->value));
}

int	is_exit_alone(char *buf)
{
	int	j;
	int	letter;

	j = -1;
	letter = 0;
	while (buf[++j])
	{
		while (buf[j] == ' ')
			j++;
		if (!(buf[j] == 'e' || buf[j] == 'x' || buf[j] == 'i'
				|| buf[j] == 't' || buf[j] == ' '))
			return (0);
		if (buf[j] != ' ')
			letter++;
	}
	if (letter != 4)
		return (0);
	return (1);
}

int	is_exit_valid(t_shell *shell, char *buf)
{
	int	j;
	int	num;
	int	no_valid;

	j = -1;
	num = 0;
	no_valid = 0;
	if (ft_strlen(shell->token->value) != 4)
		return (0);
	while (buf[++j])
	{
		if (!(buf[j] == 'e' || buf[j] == 'x' || buf[j] == 'i' || buf[j] == 't'
				|| buf[j] == ' ' || ft_isdigit(buf[j])
				|| buf[j] == '-' || buf[j] == '+'))
			no_valid++;
		if (ft_isdigit(buf[j]) || buf[j] == '-' || buf[j] == '+')
			num++;
	}
	if (num && !no_valid)
	{
		if (is_digit(shell))
			return (1);
	}
	handle_exit(shell, buf);
	return (0);
}

void	too_many_args(char **split, t_shell *shell)
{
	printf("minishell: %s: too many arguments\n", split[0]);
	shell->ret = 1;
	free_split(split);
}

void	handle_exit(t_shell *shell, char *buf)
{
	char	**split;
	int		n;
	int		is_numeric;

	if (ft_strlen(shell->token->value) != 4)
		return ;
	n = get_nb_tokens(shell);
	if (n == 1)
		free_exit(shell, buf, 1, 0);
	split = ft_split(buf, ' ');
	is_numeric = is_digit(shell);
	ft_putendl_fd("exit", 1);
	if (!split)
		return ;
	if (!is_numeric || ft_strchr(buf, '$'))
	{
		printf("%s: %s: %s: %s\n", SH, split[0], split[1], N_ARG_ER);
		is_numeric = 2;
	}
	else if (is_numeric && n > 2)
		return (too_many_args(split, shell));
	free_split(split);
	free_exit(shell, buf, 0, is_numeric);
}
