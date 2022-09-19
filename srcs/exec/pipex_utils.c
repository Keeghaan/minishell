#include "../../inc/minishell.h"

void	get_nbr_cmds(t_shell *shell)
{
	t_cmd	*tmp;
	int		i;

	shell->n_cmds = 0;
	tmp = shell->cmds;
	while (tmp)
	{
		shell->n_cmds++;
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	shell->pid = malloc(sizeof(int) * shell->n_cmds);
	if (!shell->pid)
		return ;
	i = -1;
	while (++i < shell->n_cmds)
		shell->pid[i] = -2;
}

void	cmd_not_found(t_shell *child)
{
	free(child->pid);
	free_envp(&child->envp);
	free_token(&child->token);
	free_cmds(&child->cmds);
	close(child->outfile);
	close(child->pipefd[0]);
	close(child->pipefd[1]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	path_and_cmd(t_shell *child, int index, char **envp)
{
	char	**cmd;
	char	*path;
	t_cmd	*tmp;
	int		i;

	tmp = child->cmds;
	i = 0;
	if (index == 0)
		;
	else if (child->pipe)
	{
		while (i < index)
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
			i++;
		}
	}
	cmd = tmp->full_cmd;
	path = tmp->full_path;
	if (cmd[0] && path && check_cmd(cmd[0], child->env))
		execve(path, cmd, envp);
	cmd_not_found(child);
}
