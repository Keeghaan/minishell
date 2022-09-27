/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:11:57 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/05/27 14:39:07 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_all(int fd, char *tmp, int *ret)
{
	char	*buf;
	ssize_t	bytes;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	bytes = 1;
	while (!ft_strchr_gnl(tmp, '\n') && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buf), NULL);
		if (!tmp)
			tmp = ft_strdup_gnl("");
		buf[bytes] = '\0';
		tmp = ft_strjoin_gnl(tmp, buf);
	}
	*ret = bytes;
	free(buf);
	return (tmp);
}

char	*get_the_line(char *tmp)
{
	char	*buf;
	int		i;

	i = 0;
	if (!tmp[i])
		return (NULL);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	buf = (char *)malloc(sizeof(char) * (i + 2));
	if (!buf)
		return (NULL);
	i = 0;
	while (tmp[i] && tmp[i] != '\n')
	{
		buf[i] = tmp[i];
		i++;
	}
	if (tmp[i] == '\n')
	{
		buf[i] = tmp[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}

char	*get_the_rest(char *tmp)
{
	char	*buf;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = ft_strlen_gnl(tmp);
	while (tmp[i] && tmp[i] != '\n')
		i++;
	if (!tmp[i])
		return (free(tmp), NULL);
	buf = (char *)malloc(sizeof(char) * (len - i + 1));
	if (!buf)
		return (free(tmp), NULL);
	i++;
	while (tmp[i])
	{
		buf[j] = tmp[i];
		i++;
		j++;
	}
	buf[j] = '\0';
	free(tmp);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*tmp;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		ft_free(tmp);
		return (NULL);
	}
	ret = 0;
	tmp = get_all(fd, tmp, &ret);
	if (!tmp)
		return (NULL);
	line = get_the_line(tmp);
	tmp = get_the_rest(tmp);
	if (!ret)
	{
		ft_free(tmp);
		return (NULL);
	}
	return (line);
}
