/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:18:02 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/18 20:06:22 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strjoin_bis(char *s1, char *s2, char *s3)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strlen(s1);
	while (s1[++i])
		s3[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		s3[len] = s2[i];
		len++;
	}
	s3[len] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		dup;
	char	*s3;

	dup = 0;
	if (!s2)
		return (NULL);
	if (!s1)
	{
		dup = 1;
		s1 = ft_strdup("");
	}
	if (dup)
		free(s1);
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	ft_strjoin_bis(s1, s2, s3);
	return (s3);
}
