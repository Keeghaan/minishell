/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:12:49 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/05/20 16:35:00 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1 
# endif

char	*get_all(int fd, char *tmp, int *ret);
char	*get_the_line(char *tmp);
char	*get_the_rest(char *tmp);
char	*get_next_line(int fd);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strdup_gnl(char *s);
int		ft_strchr_gnl(char *s, char c);
size_t	ft_strlen_gnl(char *s);
void	ft_free(char *tmp);
#endif
