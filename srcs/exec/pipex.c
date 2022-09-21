#include "../../inc/minishell.h"

void	child_process_bis(t_shell *child, t_cmd *tmp)
{
	if (child->outfile > -1)
		close(child->outfile);
	if (tmp->redir == 1)
		child->outfile = open(tmp->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->redir == 2)
		child->outfile = open(tmp->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		child->outfile = open(tmp->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (dup2(child->outfile, STDOUT_FILENO) == -1)
		ft_printf("minishell: %s\n", strerror(errno));
	close(child->outfile);
}

void	child_process_ter(t_shell *child, t_cmd *tmp, int index)
{
	if (index == child->n_cmds - 1 || ft_strncmp(tmp->outfile,
			"/dev/stdout", ft_strlen(tmp->outfile)))
		child_process_bis(child, tmp);
	else if (index == 0)
	{
		if (child->infile != -1)
		{
			if (dup2(child->pipefd[1], STDOUT_FILENO) == -1)
				ft_printf("minishell: %s\n", strerror(errno));
		}
	}
	else
	{
		if (dup2(child->pipefd[1], STDOUT_FILENO) == -1)
			ft_printf("minishell: %s\n", strerror(errno));
	}
}

void	child_process(t_shell *child, int index, char **envp, t_envp **env)
{
	t_cmd	*tmp;
	int		j;

	tmp = child->cmds;
	if (index != 0)
	{
		j = 0;
		while (j < index)
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				break ;
			j++;
		}
	}
	close(child->pipefd[0]);
	child_process_ter(child, tmp, index);
	close(child->pipefd[1]);
	path_and_cmd(child, index, envp, env);
}

void	pipex_bis(t_shell *child)
{
	int	i;

	i = -1;
	while (++i < child->n_cmds)
		waitpid(child->pid[i], NULL, 0);
	free(child->pid);
	if (child->pipefd[0] != -1)
		close(child->pipefd[0]);
	if (child->infile != -1)
		close(child->infile);
	dup2(child->std_in, STDIN_FILENO);
	close(child->std_in);
	dup2(child->std_out, STDOUT_FILENO);
	close(child->std_out);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
}

void	pipex(t_shell *child, char **envp, t_envp **env)
{
	int	i;

	i = -1;
	if (!child->cmds->infile)
		child->infile = -1;
	else
		child->infile = open(child->cmds->infile, O_RDONLY);
	if (child->infile < 0)
	{
		if (!double_cmd(&child->token, 1) && child->cmds->infile != NULL)
			printf("%s: %s\n", child->cmds->infile, strerror(errno));
		child->ret = 1;
	}
	else
	{
		child->ret = 0;
		double_cmd(&child->token, 1);
		if (dup2(child->infile, STDIN_FILENO) == -1)
			ft_printf("minishell: %s\n", strerror(errno));
		close(child->infile);
	}
	get_nbr_cmds(child);
	pipex_quatro(child, envp, env);
	pipex_bis(child);
}
