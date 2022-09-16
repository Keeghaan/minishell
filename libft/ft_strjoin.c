/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:18:02 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/16 17:34:43 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strjoin_bis(char *s1, char *s2, char *s3, int len1)
{
	int	i;

	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	i = -1;
	while (s2[++i])
	{
		s3[len1] = s2[i];
		len1++;
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		len1;
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
	len1 = ft_strlen(s1);
	if (dup)
		free(s1);
	s3 = (char *)malloc(sizeof(char) * (len1 + ft_strlen(s2) + 1));
	if (s3 == NULL)
		return (NULL);
	ft_strjoin_bis(s1, s2, s3, len1);
	s3[len1] = '\0';
	return (s3);
}
