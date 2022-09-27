/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nboratko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 20:20:52 by nboratko          #+#    #+#             */
/*   Updated: 2022/09/26 17:53:05 by jcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	nb_var(t_envp **envp)
{
	t_envp	*en;
	int		count;

	count = 0;
	en = *envp;
	if (!en)
		return (count);
	while (en)
	{
		count++;
		if (!en->next)
			break ;
		en = en->next;
	}
	return (count);
}

char	**env_to_char(t_envp **envp)
{
	char	**env;
	char	*tmp;
	t_envp	*en;
	int		i;

	i = 0;
	en = *envp;
	env = malloc(sizeof(char *) * nb_var(envp) + 1);
	if (!env)
		return (NULL);
	while (en)
	{
		tmp = ft_strjoin(en->var, "=");
		if (!tmp)
			return (free_split(env), NULL);
		env[i] = ft_strjoin(tmp, en->values);
		if (!env[i])
			return (free(tmp), free_split(env), NULL);
		free(tmp);
		free(env[i++]);
		if (!en->next)
			break ;
		en = en->next;
	}
	return (env);
}

void	get_nbr_cmds(t_shell *shell)
{
	t_cmd	*tmp;

	shell->n_cmds = 0;
	tmp = shell->cmds;
	while (tmp)
	{
		shell->n_cmds++;
		if (tmp->next != NULL)
			tmp = tmp->next;
		else
			break ;
	}
}

void	cmd_not_found(t_shell *child, t_envp **env)
{
	free(child->pid);
	free_envp(env);
	free_token(&child->token);
	free_cmds(&child->cmds);
	close(child->pipefd[0]);
	close(child->pipefd[1]);
	close(child->std_in);
	close(child->std_out);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void	path_and_cmd(t_shell *child, int index, char **envp, t_envp **env)
{
	t_cmd	*tmp;
	int		i;

	i = -1;
	tmp = child->cmds;
	if (index == 0)
		;
	else if (child->pipe)
	{
		while (++i < index)
		{
			if (!tmp->next)
				break ;
			tmp = tmp->next;
		}
	}
	if (tmp->full_cmd[0] && tmp->full_path && check_file(tmp->infile, 1)
		&& !is_it_builtin(child, tmp, 0))
		execve(tmp->full_path, tmp->full_cmd, envp);
	if (ft_strlen(tmp->full_cmd[0]) > 0
		&& is_it_builtin(child, child->cmds, 0))
		is_it_builtin(child, child->cmds, 1);
	cmd_not_found(child, env);
}
