/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:17:06 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/05/10 11:34:56 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_isset(char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s, const char *set)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*str;

	i = 0;
	start = 0;
	str = "";
	if (!s)
		return (NULL);
	end = ft_strlen(s) - 1;
	while (ft_isset(s[start], set))
		start++;
	if (start == (size_t)ft_strlen(s))
		return (ft_strdup(str));
	while (ft_isset(s[end], set))
		end--;
	str = malloc((end - start + 2) * sizeof(char));
	if (!str)
		return (NULL);
	while (s[start] && start <= end)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
