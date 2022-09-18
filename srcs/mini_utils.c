#include "../inc/minishell.h"

int	is_a_dir(char *value)
{
	int	fd;

	fd = open(value, O_RDWR);
	if (fd >= 0)
		return (close(fd), 2);
	fd = open(value, O_RDONLY);
	if (fd >= 0)
		return (close(fd), 3);
	return (0);
}

int	double_cmd_bis(t_token *t, int msg)
{
	int	dir;

	if (t->prev && t->prev->type == WORD && t->prev->prev
		&& t->prev->prev->type == REDIR_IN && t->prev->prev->prev
		&& t->prev->prev->prev->type == WORD
		&& t->next && t->next->type == PIPE)
	{
		if (t->empty_cmd)
		{
			if (msg)
				printf("%s: '': %s\n", t->prev->prev->prev->value,
					strerror(2));
			return (1);
		}
		else
		{
			dir = is_a_dir(t->value);
			if (dir == 3)
				return (printf("%s: %s: %s\n", t->prev->prev->prev->value,
					t->value, strerror(21)), 3);
			else if (dir == 2)
				return (2);
			if (msg && !dir)
				printf("%s: %s: %s\n", t->prev->prev->prev->value,
					t->value, strerror(2));
			return (1);
		}
	}
	return (0);
}

int	double_cmd(t_token **tok, int msg)
{
	t_token	*t;

	t = *tok;
	while (t)
	{
		if (t->type == WORD)
		{
			if (double_cmd_bis(t, msg) > 1)
				return (2);
			else if (double_cmd_bis(t, 0))
				return (1);
		}
		if (t->next)
			t = t->next;
		else
			break ;
	}
	return (0);
}

void	rewind_cmd(t_cmd **cmd, int back)
{
	if (back)
	{
		while (*cmd)
		{
			if ((*cmd)->prev)
				*cmd = (*cmd)->prev;
			else
				break ;
		}
	}
	else
	{
		while (*cmd)
		{
			if ((*cmd)->next)
				*cmd = (*cmd)->next;
			else
				break ;
		}
	}
}

void	rewind_token(t_token **token, int back)
{
	if (back)
	{
		while (*token)
		{
			if ((*token)->prev)
				*token = (*token)->prev;
			else
				break ;
		}
	}
	else
	{
		while (*token)
		{
			if ((*token)->next)
				*token = (*token)->next;
			else
				break ;
		}
	}
}
