#include "../inc/minishell.h"

void	init_shell_struct(t_shell *shell)
{
	//shell->pid = 0; // ca non plus, peut-etre pas besoin :D
	t_cmd	*tmp;

	tmp = shell->cmds;
	while (tmp)
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	if (tmp->redir == 1)
		shell->outfile = open(tmp->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->redir == 2)
		shell->outfile = open(tmp->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	free_cmds(t_cmd **cmd)
{
	t_cmd	*tmp;
	int	i;

	tmp = *cmd;
	while (tmp)
	{
		i = 0;
		*cmd = (*cmd)->next;
		if (tmp->full_path)
			free(tmp->full_path);
		while (tmp->full_cmd[i])
		{
			free(tmp->full_cmd[i]);
			i++;
		}
		free(tmp->full_cmd);
		if (tmp)
			free(tmp);
		tmp = *cmd;
	}
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
