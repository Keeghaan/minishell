/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 14:34:33 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/09/16 11:42:38 by jcourtoi         ###   ########.fr       */
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

int	is_exit_alone(char *buf)
{
	int	j;

	j = -1;
	while (buf[++j])
	{
		if (!(buf[j] == 'e' || buf[j] == 'x' || buf[j] == 'i' || buf[j] == 't' || buf[j] == ' '))
			return (0);	
	}
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
	printf("EEEEH\n");//
	while (buf[++j])
	{
		if (!(buf[j] == 'e' || buf[j] == 'x' || buf[j] == 'i' || buf[j] == 't' || buf[j] == ' ' || ft_isdigit(buf[j]) || buf[j] == '-' || buf[j] == '+'))
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
	//cette fonction est chelou j'espere qu'elle ne cassera rien 
}

void	handle_exit(t_shell *shell, char *buf)
{
	char	**split;
	int	n;
	int	is_numeric;

	n = get_nb_tokens(shell);
	if (n == 1)
	{
		ft_putendl_fd("exit", 1);
		free_exit(shell);
	}
	split = ft_split(buf, ' ');
	is_numeric = is_digit(shell);
	ft_putendl_fd("exit", 1);
	if (!split)
		return ;
	if (!is_numeric)
		printf("minishell: %s: %s: numeric argument required\n", split[0], split[1]);
	else if (is_numeric && n > 2)
	{
		printf("minishell: %s: too many arguments\n", split[0]);
		free_split(split);
		return ;
	}
	free_split(split);
	free_exit(shell);
}
