#include "../../inc/minishell.h"

static void	free_all(t_shell *shell)
{
	free_envp(&shell->envp);
	free_token(&shell->token);
	free_cmds(&shell->cmds);
}

static int	write_here_doc(char **tmp, int *file, char *heredoc, t_shell *shell)
{
	int	cmp;

	*tmp = readline("> ");
	if (!(*tmp) && g_return != 130)
	{
		printf("minishell: warning : here-document limited");
		printf("by end-of-file (wanted `%s')\n", heredoc);
		return (0);
	}
	if (!(*tmp) && g_return == 130)
	{
		free_all(shell);
		return (130);
	}
	if (ft_strlen(*tmp) == ft_strlen(heredoc))
		cmp = ft_strncmp(heredoc, *tmp, ft_strlen(heredoc));
	else
		cmp = 1;
	if (!cmp)
		return (0);
	if ((*tmp)[0] == '$')
		expand_tmp(tmp, shell, heredoc);
	write(*file, *tmp, ft_strlen(*tmp));
	write(*file, "\n", 1);
	free(*tmp);
	return (1);
}

static int	write_in_file(int *file, t_token **token, t_shell *shell, int a)
{
	int		check;
	char	*tmp;
	struct sigaction	sa;

	check = 1;
	if (*file == -1)
		ft_printf("%s\n", strerror(errno));
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_mister_here;
	sa.sa_flags = SA_RESTART;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		if (!a)
			check = write_here_doc(&tmp, file, (*token)->next->next->value, shell);
		else
		{	
			check = write_here_doc(&tmp, file, (*token)->next->value, shell);
		}
		if (check == 0)
			break ;
		if (check == 130)
			return (130);
	}
	free(tmp);
	close(*file);
	return (0);
}

static int	parent_process(t_cmd **new, int a)
{
	int	status;

	waitpid(-1, &status, 0);
	if (!a)
	{
		free(*new);
		*new = malloc(sizeof(t_cmd));
		if (WEXITSTATUS(status) == 130)
			(*new)->infile = NULL;
		else if (WEXITSTATUS(status) == 0)
			(*new)->infile = ".here_doc";
	}
	if (WEXITSTATUS(status) == 130)
		return (130);
	g_return = WEXITSTATUS(status);
	return (0);
}

int	get_here_doc(t_token **token, t_cmd **new, t_shell *shell, int a)
{
	int			file;
	pid_t	lol;

	signal(SIGINT, SIG_IGN);
	if (a)
		(void)(*new);
	file = 0;	
	lol = fork();
	file = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (lol == 0)
	{
		if (write_in_file(&file, token, shell, a) == 130)
		{
			if (!a)
				free(*new);
			exit(130);
		}
		free_all(shell);
		if (!a)
			free(*new);
		exit(0);
	}
	else
		return (parent_process(new, a));
	return (1);
}

	/*
	static int	i;
	if (lol == 0)
	{
		if (i != 1)
		{
			file = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write_in_file(&file, token);
			(*new)->infile = ".here_doc";
			i = 1;
			exit(0);
		}
		else
		{
			file = open(".here_doc2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			write_in_file(&file, token);
			(*new)->infile = ".here_doc2";
			i = 0;
			exit(0);
	}*/

