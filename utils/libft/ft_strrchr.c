/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 18:32:59 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/03 18:42:12 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ps;

	i = ft_strlen(s);
	ps = (char *)s;
	while (i >= 0)
	{
		if (ps[i] == (unsigned char)c)
			return (&ps[i]);
		i--;
	}
	return (NULL);
}
