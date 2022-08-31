/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:10:21 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/11/25 18:26:08 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t n)
{
	unsigned char	*pb;
	unsigned int	i;

	pb = (unsigned char *)b;
	i = 0;
	while (i < n)
	{
		pb[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
