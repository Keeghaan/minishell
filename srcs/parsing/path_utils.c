#include "../../inc/minishell.h"

char	**get_paths(t_shell *shell, char *cmd, t_envp **envp)
{
	char	**paths;
	t_envp	*tmp;

	tmp = *envp;
	while (tmp && ft_strncmp(tmp->var, "PATH", 4))
	{
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}	
	if (tmp == NULL || !ft_strncmp(tmp->var, "LD", 2) || !tmp->next)
	{
		free(shell->env[0]);
		free(shell->env[1]);
		shell->env[0] = ft_strdup("");
		shell->env[1] = ft_strdup("");
		ft_printf("minishell: %s: %s\n", cmd, "No such file or directory");
		return (NULL);
	}
	paths = NULL;
	if (tmp)
		paths = ft_split(tmp->values, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*get_full_path(t_shell *shell, char *cmd)
{
	char	**paths;
	char	*slash;
	char	*path;
	int		i;

	i = 0;
	paths = get_paths(shell, cmd, &shell->envp);
	if (!paths)
		return (NULL);
	if (cmd && ft_strnstr(cmd, "/", ft_strlen(cmd))
		&& access(cmd, X_OK | F_OK | R_OK) == 0)
		return (free_split(paths), cmd);
	while (paths[i++])
	{
		slash = ft_strjoin_original(paths[i], "/");
		path = ft_strjoin_original(slash, cmd);
		free(slash);
		if (!path)
			return (free_split(paths), NULL);
		if (access(path, X_OK | F_OK | R_OK) == 0)
			return (free_split(paths), path);
		free(path);
	}
	free_split(paths);
	return (NULL);
}
