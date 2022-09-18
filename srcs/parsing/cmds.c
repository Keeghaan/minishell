#include "../../inc/minishell.h"

int	is_builtin(t_token **tmp)
{
	if (!ft_strncmp((*tmp)->value, "echo", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "cd", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "unset", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "export", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "pwd", ft_strlen((*tmp)->value))
		|| !ft_strncmp((*tmp)->value, "exit", ft_strlen((*tmp)->value)))
		return (1);
	return (0);
}

void	add_new_cmd(t_cmd **cmd, t_token **tmp, t_shell *shell)
{
	t_cmd	*tmp_cmd;

	tmp_cmd = *cmd;
	while (tmp_cmd->next)
		tmp_cmd = tmp_cmd->next;
	tmp_cmd->next = make_new_cmd(tmp, shell);
	tmp_cmd->next->prev = tmp_cmd;
}

void	get_infile(t_token **tmp, t_cmd **new)
{
	t_token	*token;

	token = *tmp;
	if (((*tmp)->prev == NULL || (*tmp)->prev->type == PIPE)
		&& (*tmp)->next && (*tmp)->next->type != REDIR_IN)
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->prev == NULL && ((*tmp)->next == NULL
			|| (*tmp)->next->type == PIPE))
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->prev && (*tmp)->prev->type == PIPE)
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->next && (*tmp)->next->type
		== REDIR_IN && (*tmp)->next->next)
	{
		token = token->next->next;
		while (token->next && token->next->next && token->next->type == WORD
			&& token->next->next->type == PIPE)
			token = token->next;
		(*new)->infile = token->value;
	}		
	else if ((*tmp)->prev->prev && (*tmp)->prev->prev->type == REDIR_IN
		&& !(*tmp)->prev->prev->prev)
		(*new)->infile = (*tmp)->prev->value;
	else
		(*new)->infile = "/dev/stdin"; //
}

void	get_outfile(t_token **tmp, t_cmd **new)
{	
	if ((*tmp)->type == REDIR_OUT)
		(*new)->outfile = (*tmp)->next->value;
	else if ((*tmp)->prev == NULL && (*tmp)->next == NULL)
		(*new)->outfile = "/dev/stdout";
	else if ((*tmp)->type == PIPE)
		(*new)->outfile = "/dev/stdout";
	else if ((*tmp)->type == DREDIR_IN)
	{
		if ((*tmp)->next->next && (*tmp)->next->next->type == PIPE)
			(*new)->outfile = "/dev/stdout";
		else if ((*tmp)->next->next && (*tmp)->next->next->next
			&& (*tmp)->next->next->type == REDIR_OUT)
			(*new)->outfile = (*tmp)->next->next->next->value;
	}
	else
		(*new)->outfile = "/dev/stdout";
	(*new)->redir = 1;
	if ((*tmp)->type == DREDIR_OUT)
	{
		(*new)->outfile = (*tmp)->next->value;
		(*new)->redir = 2;
	}
}

t_cmd	*make_new_cmd(t_token **tmp, t_shell *shell)
{
	t_cmd	*new;
	t_token	*curr;
	int		i;
	int		count;

	count = 0;
	i = 0;
	curr = *tmp;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->empty = 0;
	if ((*tmp)->next && (*tmp)->next->type == DREDIR_IN)
		get_here_doc(tmp, &new);
	else
		get_infile(tmp, &new);
	while (curr)
	{
		count += ft_strlen(curr->value) + 1;
		if (curr->next)
			curr = curr->next;
		else
			break ;
	}
	new->redir = 0;
	if ((*tmp)->empty_cmd)
		new->empty = 1;
	new->full_cmd = (char **)malloc(sizeof(char *) * count);
	if (!new->full_cmd)
		return (NULL);
	i = 0;
	while (*tmp && (*tmp)->type == WORD)
	{
		new->full_cmd[i] = ft_strdup(((*tmp)->value));
		if (!new->full_cmd[i])
			return (free_split(new->full_cmd), NULL);
		i++;
		if ((*tmp)->next)
			*tmp = (*tmp)->next;
		else
			break ;
	}
	get_outfile(tmp, &new);
	new->full_cmd[i] = NULL;
	new->full_path = get_full_path(shell, new->full_cmd[0]);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
