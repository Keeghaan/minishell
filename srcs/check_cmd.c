/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 12:12:26 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/29 13:23:19 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_cmd(t_shell *shell, char *buf)
{
	int		j;
	int		count;
	char	**split;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
(void)shell;
	tmp3 = "";
	split = ft_split(buf, ' ');
	if (!split)
		return ;
	j = -1;
	count = 0;
	tmp = ft_strnstr(buf, "cd", ft_strlen(buf));
	if (tmp)
	{
		printf("%s\n", tmp);
		while (tmp[++j])
		{
			if (tmp[j] == ' ' && !count)
				count++;
			if (tmp[j] == ' ' && count)
				tmp2 = ft_strnstr(&tmp[j], &tmp[j], ft_strlen(&tmp[j]));
			ft_strlcpy(tmp3, tmp, ft_strlen(tmp) - ft_strlen(tmp2));
		}
		printf("%s\n", tmp3);
	}
		/*
	while (split[++j])
	{
		if (!ft_strncmp(split[j], "cd", ft_strlen(split[j])))
		{
			tmp = ft_strjoin(split[j], );
		       	tmp2 = ft_strjoin(tmp, split[j + 1]);
			j++;
			printf("%s\n", tmp);
		}
	}*/
	free(split);
}
