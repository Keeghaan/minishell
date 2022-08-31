/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 20:30:07 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/05/27 11:30:32 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned int	**ptr;
	unsigned int	i;

	ptr = malloc(size * count);
	if (!ptr)
		return (NULL);
	i = 0;
	if (size == 0)
		return ((void *)ptr);
	while (i < count)
	{
		ft_bzero(ptr, count * size);
		i++;
	}
	return ((void *)ptr);
}
