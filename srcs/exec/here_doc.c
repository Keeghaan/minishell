#include "../../inc/minishell.h"

static void	handle_mister_here(int sig)
{
	(void)sig;
	g_return = 130;
	if (STDIN_FILENO != -1)
		close(STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
}

/*static void	new_func(t_shell *shell, t_cmd **new)
{
	t_cmd	*cmd;
	
	cmd = shell->cmds;
	if (!cmd)
	{
		cmd = *new;
		shell->cmds = cmd;
		return ;
	}
	else if (cmd && !cmd->next)
	{
		cmd->next = *new;
		return ;
	}
	if (cmd && cmd->next)
	{
		while (cmd->next)
			cmd = cmd->next;
	}
	cmd->next = *new;
	
}*/

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
		
		free_envp(&shell->envp);
		free_token(&shell->token);
		free_cmds(&shell->cmds);
		return (130);
	}
	if (ft_strlen(*tmp) == ft_strlen(heredoc))
		cmp = ft_strncmp(heredoc, *tmp, ft_strlen(heredoc + 1));
	else
		cmp = 1;
	if (!cmp)
		return (0);
	write(*file, *tmp, ft_strlen(*tmp));
	write(*file, "\n", 1);
	free(*tmp);
	return (1);
}

static int	write_in_file(int *file, t_token **token, t_shell *shell)
{
	int		check;
	char	*tmp;
	struct sigaction	sa;

	//*file = open("/tmp/file1", O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	check = 1;
	if (*file == -1)
		ft_printf("%s\n", strerror(errno));
	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &handle_mister_here;
	sa.sa_flags = SA_RESTART;
	while (1)
	{
		sigaction(SIGINT, &sa, NULL);
		check = write_here_doc(&tmp, file, (*token)->next->next->value, shell);
		if (check == 0)
			break ;
		if (check == 130)
			return (130);
	}
	free(tmp);
	close(*file);
	return (0);
}

int	get_here_doc(t_token **token, t_cmd **new, t_shell *shell)
{
	int			file;
	pid_t	lol;
	int	status;

	signal(SIGINT, SIG_IGN);
	file = 0;	
	lol = fork();
	file = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (lol == 0)
	{
		if (write_in_file(&file, token, shell) == 130)
		{
			free(*new);
			exit(130);
		}
		free_envp(&shell->envp);
		free_token(&shell->token);
		free_cmds(&shell->cmds);
		free(*new);
		exit(0);
	}
	else
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 130)
			(*new)->infile = NULL;
		else if (WEXITSTATUS(status) == 0)
			(*new)->infile = ".here_doc";
	}
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

