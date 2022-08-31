/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:29:13 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/12/03 18:39:51 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	unsigned int	i;
	unsigned char	pc;

	ps = (unsigned char *)s;
	pc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (ps[i] == pc)
			return ((void *)ps + i);
		i++;
	}
	return (NULL);
}
