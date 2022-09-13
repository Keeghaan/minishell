#include "../../inc/minishell.h"

static void	child_process(t_shell *child, int index)
{
	t_cmd	*tmp;
	int	j;

	tmp = child->cmds;
	if (index == 0)
		;
	else
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
	if (index == child->n_cmds - 1 || ft_strncmp(tmp->outfile, "/dev/stdout", ft_strlen(tmp->outfile)))
	{
		close(child->outfile);
		dup2(child->std_out, 1);
		if (tmp->redir == 1)	
			child->outfile = open(tmp->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp->redir == 2)
			child->outfile = open(tmp->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			child->outfile = open(tmp->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644); //test pour si y a pas de redir
		if (dup2(child->outfile, STDOUT_FILENO) == -1)
			ft_printf("minishell: %s\n", strerror(errno));
		close(child->outfile);
	}
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
	close(child->pipefd[1]);
	path_and_cmd(child, index);
}

static void	pipex_loop2(t_shell *child, int i)
{
	close(child->pipefd[0]);
	if (i == 0)
	{
		if (child->infile != -1)
			child_process(child, i);
	}
	if (i > 0)
		child_process(child, i);
}

static void	pipex_loop(t_shell *child, int i)
{
	t_cmd *tmp;
	int	j;
	
	tmp = child->cmds;
	if (i == 0)
		;
	else
	{
		j = 0;
		while (j < i)
		{
			if (tmp->next)
				tmp = tmp->next;
			else
				break;
			j++;
		}
	}
	if (i > 0)
	{
		if (ft_strncmp(tmp->infile, "/dev/stdin", ft_strlen(tmp->infile)))
		{
			dup2(child->std_in, 0);
			child->infile = open(tmp->infile, O_RDONLY);
			if (dup2(child->infile, STDIN_FILENO) == -1)
				ft_printf("minishell: %s\n", strerror(errno));
			close(child->infile);
		}
		else
		{
			if (dup2(child->pipefd[0], STDIN_FILENO) == -1)
				ft_printf("minishell: %s %s\n", strerror(errno));
			close(child->pipefd[0]);
		}
	}
	if (pipe(child->pipefd) == -1)
		ft_printf("minishell: %s\n", strerror(errno));
	if (i == 0)
	{
		if (child->infile != -1)
			child->pid[i] = fork();
	}
	if (i > 0)
		child->pid[i] = fork();
	if (child->pid[i] == -1)
		ft_printf("minishell: %s %s\n", strerror(errno));
	if (child->pid[i] == 0)
		pipex_loop2(child, i);
}

void	get_nbr_cmds(t_shell *shell)
{
	t_cmd	*tmp;
	int	i;

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

void	pipex(t_shell *child)
{
	int	i;
	int	status;

	i = -1;
	//if (!child->here_doc)
	child->infile = open(child->cmds->infile, O_RDONLY);
	if (child->infile < 0)
		printf("%s: %s\n", child->cmds->infile, strerror(errno));
	else
	{
		if (dup2(child->infile, STDIN_FILENO) == -1)
			ft_printf("minishell: %s\n", strerror(errno));
		close(child->infile);
	}
	get_nbr_cmds(child);
	while (++i < child->n_cmds)
	{
		pipex_loop(child, i);
		close(STDIN_FILENO);
		close(child->pipefd[1]);
	}
	i = -1;
	while (++i < child->n_cmds)
		waitpid(child->pid[i], &status, 0);
	free(child->pid);
	if (child->pipefd[0] != -1)
		close(child->pipefd[0]);
	if (child->infile != -1)
		close(child->infile);
	dup2(child->std_in, 0);
	dup2(child->std_out, 1);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	if (access(".here_doc2", F_OK) == 0)
		unlink(".here_doc2");
	//close(child->std_in);
	//close(child->std_out);
}
