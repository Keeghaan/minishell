#include "../../inc/minishell.h"

static void	child_process(t_shell *child, int index)
{
	close(child->pipefd[0]);
	if (index == child->n_cmds - 1)
	{
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
	//struct sigaction	s;

	//s.sa_handler = SIG_DFL;
	//sigaction(SIGQUIT, &s, NULL);
	signal(SIGQUIT, SIG_DFL);
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
	if (i > 0)
	{
		if (dup2(child->pipefd[0], STDIN_FILENO) == -1)
			ft_printf("minishell: %s %s\n", strerror(errno));
		close(child->pipefd[0]);
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
	shell->pid = malloc(sizeof(int) * 2);
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
	if (child->infile != -1)
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
	if (child->pipefd[0] != -1)
		close(child->pipefd[0]);
	if (child->infile != -1)
		close(child->infile);
	dup2(child->std_in, 0);
	dup2(child->std_out, 1);
//	signalisation();
}

