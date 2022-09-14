#include "../inc/minishell.h"
#include <fcntl.h>

int	g_return;

void	no_cmd(t_shell *shell, t_token **token, char **envp)
{
	(void)shell;
	int	cases; //fonction en cours mais en fait j'ai l'impression qu'elle ne servira a rien et qu'il faudra juste utiliser which_case xD je sais pu pourquoi jai fait cette fonction intermediaire a la base

	cases = which_case(token, envp);
	if (cases == 1)
		printf("case 1\n");
	else if (cases == 2)
		printf("case 2\n");
	else
		printf("else\n");
}


void	shell_loop_part_two(char *buf, t_shell *shell, t_token **token, char **envp, t_envp **env)
{
	if (ft_strchr(buf, '|'))
		shell->pipe = 1;
	else
		shell->pipe = 0;
	g_return = shell->ret;
	if (tokenizer(buf, token, env))
		ft_putendl_fd("minishell: syntax error", 2);
	if (!(*token))
	{
		return ;
	}
	shell->token = *token;
	/*if (ft_strnstr(buf, "exit", ft_strlen(buf)) && is_exit_valid(shell, buf))
	{
		ft_putendl_fd("exit", 1);
		free(buf);
		free_exit(shell);
	}*/
	if (!ft_strncmp(buf, "exit", ft_strlen("exit")) && ft_strlen(buf) > 5) //a optimiser
		handle_exit(shell, buf);
	else if (ft_strnstr(buf, "exit", ft_strlen(buf)) && is_exit_valid(shell, buf))
	{
		ft_putendl_fd("exit", 1);
		free(buf);
		free_exit(shell);
	}
	else
	{
		parse(token, shell);
		if (shell->cmds)
		{
			init_shell_struct(shell);
			run_cmd(shell, envp);
		}
		else
			no_cmd(shell, token, envp);
	}
//	free_token(&shell->token);
//	error_msg(shell, shell->cmds, envp, 0);
}

void	main_shell_loop(t_envp **env, t_shell *shell, t_token **token, char **envp)
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
			shell_loop_part_two(buf, shell, token, envp, env);
		if (buf)
			free(buf);
	}
}

void	run_shell(t_envp **env, t_shell *shell, char **envp)
{

	t_token	*token;
	
	ft_memset(&token, 0, sizeof(token));
	ft_memset(&shell->cmds, 0, sizeof(shell->cmds));
	shell->is_running = 1;
	while (shell->is_running)
	{
		signalisation(0);
		if (*env)
			shell->envp = *env;
		getcwd(shell->cwd, sizeof(shell->cwd));
		shell->n_cmds = 0; // ?
		main_shell_loop(env, shell, &token, envp);
		if (shell->cmds)
			free_cmds(&shell->cmds);
		if (token)
			free_token(&token);
			
	}
//	if (shell->cmds)
//		free_cmds(&shell->cmds); //????pour les leaks d'exit
	if (shell->prev_dir)
		free(shell->prev_dir);
	if (shell->next_dir)
		free(shell->next_dir);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*env;
	t_shell	shell;

	//g_return = 125;
	check_argv(&shell, argc, argv, envp);
	envp_to_lst(&env, envp);
	init_shell(&shell);
	shell.std_in = dup(0);
	shell.std_out = dup(1);
//	shell.env = envp;
	run_shell(&env, &shell, envp);
	if (env)
		free_envp(&env);
//	free_cmds(&shell.cmds);
	if (shell.env)
		free_split(shell.env);
	return (0);
}
