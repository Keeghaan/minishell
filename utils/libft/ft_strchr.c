/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 17:24:25 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/01 18:07:20 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ps;

	i = 0;
	ps = (char *)s;
	while (ps[i])
	{
		if (ps[i] == (char)c)
			return ((char *)&ps[i]);
		i++;
	}
	if (ps[i] == (char)c)
		return ((char *)&ps[i]);
	return (NULL);
}
