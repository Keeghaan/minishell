#include "../inc/minishell.h"
#include <fcntl.h>

int	g_return;

static	int	shell_loop_part_two_bis(char *buf, t_shell *shell,
		t_token **token, t_envp **env)
{
	shell->unclosed_q = 0;
	g_return = shell->ret;
	if (ft_strchr(buf, '|'))
		shell->pipe = 1;
	else
		shell->pipe = 0;
	if (tokenizer(buf, token))
	{
		ft_putendl_fd("minishell: syntax error", 2);
		shell->unclosed_q = 1;
	}
	if (!(*token))
		return (1);
	if ((*token)->value)
		expander(token, env);
	shell->token = *token;
	return (0);
}

static void	shell_loop_part_two(char *buf, t_shell *shell,
		t_token **token, t_envp **env)
{
	shell_loop_part_two_bis(buf, shell, token, env);
	if (!ft_strncmp(buf, "exit", ft_strlen("exit")) && ft_strlen(buf) > 5)
		handle_exit(shell, buf);
	else if (ft_strnstr(buf, "exit", ft_strlen(buf))
		&& is_exit_valid(shell, buf))
		free_exit(shell, buf, 1);
	else
	{
		if (parse(token, shell) == -1)
			return ;
		shell_loop_ter(shell, token);
		if (shell->next_dir)
		{
			free(shell->next_dir);
			shell->next_dir = NULL;
		}
	}
}

void	main_shell_loop(t_envp **env, t_shell *shell, t_token **token)
{
	char	*buf;

	buf = readline("\033[1;31m<3\033[0m  ");
	if (!buf)
	{
		shell->is_running = 0;
		ft_putendl_fd("exit", 2);
	}
	else
	{
		if (ft_strlen(buf) >= 4 && !ft_strncmp("exit", buf, ft_strlen(buf)))
		{
			shell->is_running = 0;
			ft_putendl_fd("exit", 1);
			return (free(buf));
		}
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (*buf != '\0' && *buf != '\n')
			shell_loop_part_two(buf, shell, token, env);
		if (buf)
			free(buf);
		if (token)
			free_token(token);
	}
}

void	run_shell(t_envp **env, t_shell *shell)
{
	t_token	*token;

	ft_memset(&token, 0, sizeof(token));
	ft_memset(&shell->cmds, 0, sizeof(shell->cmds));
	shell->is_running = 1;
	shell->ret = 0;
	while (shell->is_running)
	{
		signalisation(0);
		shell->envp = *env;
		getcwd(shell->cwd, sizeof(shell->cwd));
		shell->n_cmds = 0;
		shell->std_in = dup(STDIN_FILENO);
		shell->std_out = dup(STDOUT_FILENO);
		main_shell_loop(env, shell, &token);
		if (shell->cmds != NULL)
			free_cmds(&shell->cmds);
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*env;
	t_shell	shell;

	check_argv(argc, argv, envp);
	envp_to_lst(&env, envp);
	init_shell(&shell);
	shell.env = envp;
	run_shell(&env, &shell);
	if (env)
		free_envp(&env);
	close(shell.std_in);
	close(shell.std_out);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (0);
}
