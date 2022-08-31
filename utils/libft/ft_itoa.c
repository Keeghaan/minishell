/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:24:12 by jcourtoi          #+#    #+#             */
/*   Updated: 2021/11/25 16:10:22 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	string_size(long int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n > 9)
	{
		count++;
		n = n / 10;
	}		
	if (n < 10)
		count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*string;
	int		size;
	long	nb;

	nb = n;
	size = string_size(n);
	string = malloc(sizeof(char) * size + 1);
	if (!(string))
		return (NULL);
	string[size--] = '\0';
	if (nb == 0)
		string[0] = 48;
	if (nb < 0)
	{
		nb *= -1;
		string[0] = '-';
	}
	while (nb > 0)
	{
		string[size] = (nb % 10) + 48;
		nb = nb / 10;
		size--;
	}
	return (string);
}
