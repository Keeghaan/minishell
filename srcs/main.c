#include "../inc/minishell.h"
#include <fcntl.h>

void	main_shell_loop(t_envp **env, t_shell *shell, t_token **token, char **envp)
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
			if (tokenizer(buf, token, env))
				ft_putendl_fd("minishell: syntax error", 2);
			shell->token = *token;
			parse(token, shell);
			init_shell_struct(shell);
			run_cmd(shell, envp);
			free_token(&shell->token);
		
		}
	//	signalisation();
		
	//	write(1, "\n", 1);
	//	pipex(shell);
		if (buf)
			free(buf);
		//free_cmds(&shell->cmds);
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
	//	signalisation();
//		if (shell->cmds)
//			free_cmds(&shell->cmds);
	}
	free(shell->prev_dir);
	free(shell->next_dir);
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	t_envp	*env;
	t_shell	shell;

	check_argv(argc, argv, envp);
	envp_to_lst(&env, envp);
	shell.std_in = dup(0);
	shell.std_out = dup(1);
	shell.env = envp;
	run_shell(&env, &shell, envp);
	if (env)
		free_envp(&env);
	return (0);
}
