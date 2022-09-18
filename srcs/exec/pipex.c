#include "../../inc/minishell.h"

void	child_process_bis(t_shell *child, t_cmd *tmp)
{
	close(child->outfile);
	dup2(child->std_out, 1);
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

void	child_process(t_shell *child, int index, char **envp)
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
	path_and_cmd(child, index, envp);
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
	dup2(child->std_in, 0);
	dup2(child->std_out, 1);
	if (access(".here_doc", F_OK) == 0)
		unlink(".here_doc");
	if (access(".here_doc2", F_OK) == 0)
		unlink(".here_doc2");
}
/*
int	double_cmd(t_token **tok)
{
	t_token *t;

	t = *tok;
	while (t)
	{
		if (t->type == WORD)
		{
			if (t->prev && t->prev->type == WORD && t->prev->prev && t->prev->prev->type
				== REDIR_IN && t->prev->prev->prev && t->prev->prev->prev->type == WORD && t->next && t->next->type == PIPE)
			{
				if (t->empty_cmd)
					return (printf("%s: '': %s\n", t->prev->prev->prev->value, strerror(2)), 1);
				else
					return (printf("%s: %s: %s\n", t->prev->prev->prev->value, t->value, strerror(2)), 1);
			}
		}
		if (t->next)
			t = t->next;
		else
			break ;
	}
	return (0);
}
*/
void	pipex(t_shell *child, char **envp)
{
	int	i;

	i = -1;
	child->infile = open(child->cmds->infile, O_RDONLY);
	if (child->infile < 0)
	{
		if (!double_cmd(&child->token))
			printf("%s: %s\n", child->cmds->infile, strerror(errno));
	}
	else
	{
		if (dup2(child->infile, STDIN_FILENO) == -1)
			ft_printf("minishell: %s\n", strerror(errno));
		close(child->infile);
	}
	get_nbr_cmds(child);
	while (++i < child->n_cmds)
	{
		pipex_loop(child, i, envp);
		close(STDIN_FILENO);
		close(child->pipefd[1]);
	}
	pipex_bis(child);
}
