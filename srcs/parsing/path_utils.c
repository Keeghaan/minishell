#include "../../inc/minishell.h"

char	**get_paths(char *cmd, t_envp **envp) //from pipex
{
	char	**paths;
	t_envp	*tmp;
	
	tmp = *envp;
	while (ft_strncmp(tmp->var, "PATH", 4))
	{
			tmp = tmp->next; //ca leak
	}
	if (!ft_strncmp(tmp->var, "LD", 2))
		ft_printf("minishell: %s: %s\n", cmd, "No such file or directory");
	paths = NULL;
	if (tmp)
		paths = ft_split(tmp->values, ':');
	if (paths == NULL)
		return (NULL);
	return (paths);
}

char	*get_full_path(t_shell *shell, char *cmd) //from pipex 
{
	char	**paths;
	char	*slash;
	char	*path;
	int		i;

	i = 0;	
	paths = get_paths(cmd, &shell->envp);
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
