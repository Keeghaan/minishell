#include "../inc/minishell.h"
#include <fcntl.h>

void	main_shell_loop(t_envp **env, t_shell *shell, t_token **token, char **envp)
{
	char	*buf;

	buf = readline("<3  ");
	if (!buf) //pour ctrl+D ou exit, mais exit, on va devoir faire un builin finalement car dans la correction ils demandent un comportement different s'il y a des arguments apres exit (comme dans le vrai shell)
	{
		shell->is_running = 0;
		ft_putendl_fd("exit", 2);
	}
	else
	{
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (tokenizer(buf, token, env))
			ft_putendl_fd("minishell: syntax error", 2);
		shell->token = *token;
		parse(token, shell);
		init_shell_struct(shell);
		run_cmd(shell, envp);
	//	pipex(shell);
		if (buf)
			free(buf);
		free_token(&shell->token);
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
		signalisation();
		if (*env)
			shell->envp = *env;
		main_shell_loop(env, shell, &token, envp);
		if (shell->cmds)
			free_cmds(&shell->cmds);
		signalisation();
	}
	rl_clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_envp	*env;
	t_shell	shell;

	envp_to_lst(&env, envp);
	shell.env = envp;
	run_shell(&env, &shell, envp);
	if (env)
		free_envp(&env);
	return (0);
}
