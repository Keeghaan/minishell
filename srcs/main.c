#include "../inc/minishell.h"
#include <fcntl.h>

int	g_return;

void	no_cmd(t_shell *shell, t_token **token, char **envp)
{
	(void)shell;
	int	cases;

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
	if (!ft_strncmp(buf, "exit", ft_strlen("exit")) && ft_strlen(buf) > 5) //a optimiser
		handle_exit(shell, buf);
	else
	{
		parse(token, shell);
		if (shell->cmds)
		{
			printf("shell loop cmds 2 test\n");
			init_shell_struct(shell);
			run_cmd(shell, envp);
		}
		else
			no_cmd(shell, token, envp);
	}
	free_token(&shell->token);
	error_msg(shell, shell->cmds, envp, 0);
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


/*void	main_shell_loop(t_envp **env, t_shell *shell, t_token **token, char **envp)
{
	char	*buf;

//printf("hello"); //
	buf = readline("\033[1;31m<3\033[0m  ");
	if (!buf) //pour ctrl+D ou exit, mais exit, on va devoir faire un builin finalement car dans la correction ils demandent un comportement different s'il y a des arguments apres exit (comme dans le vrai shell)
	{
		shell->is_running = 0;
		ft_putendl_fd("exit", 2);
	}
	else
	{
		if (!ft_strncmp(buf, "exit", ft_strlen("exit")) && ft_strlen(buf) > 5) //a optimiser
			handle_exit(shell, buf);
		if (ft_strlen(buf) >= 4 && !ft_strncmp("exit", buf, ft_strlen(buf)))
		{
			shell->is_running = 0;
			ft_putendl_fd("exit", 1);
			return (free(buf));
		}
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (*buf != '\0' && *buf != '\n')
		{
			if (ft_strchr(buf, '|'))
				shell->pipe = 1;
			else
				shell->pipe = 0;
			g_return = shell->ret;
			if (tokenizer(buf, token, env))
			{
				ft_putendl_fd("minishell: syntax error", 2);
			}
			shell->token = *token;
			parse(token, shell);
			init_shell_struct(shell);
			run_cmd(shell, envp);
			free_token(&shell->token);
			error_msg(shell, shell->cmds, envp, 0);
		}
	//	signalisation();
		
	//	write(1, "\n", 1);
	//	pipex(shell);
		if (buf)
			free(buf);
		//free_cmds(&shell->cmds);
	}
}*/

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
		{
			printf("free cmds ? (test run shell)\n");
			free_cmds(&shell->cmds);
		}
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
	free_split(shell.env);
	//close(shell.std_in);
	//close(shell.std_out);
	return (0);
}
