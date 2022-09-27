/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 16:16:11 by jcourtoi          #+#    #+#             */
/*   Updated: 2022/07/29 13:36:02 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	get_prompt(int fd)
{
	char	*tmp;

	write(1, "<^-^> ", 6);
	tmp = get_next_line(STDIN_FILENO);
	if (!tmp)
		return ;
	write(fd, tmp, ft_strlen(tmp));
	free(tmp);
}

int	get_history(t_shell *shell)
{
	int		fd;

	fd = open(".history", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (1);
	get_prompt(fd);
	close(fd);
	get_next_line(-1);
	shell->history = open(".history", O_RDONLY);
	if (shell->history == -1)
		return (unlink(".history"), 3);
	return (0);
}

int	main(void)
{
	t_shell	shell;

	get_history(&shell);
}
