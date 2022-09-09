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
	if (((*tmp)->prev == NULL || (*tmp)->prev->type == PIPE) && (*tmp)->next && (*tmp)->next->type != REDIR_IN)
		(*new)->infile = "/dev/stdin"; //par defaut
	else if ((*tmp)->prev == NULL && ((*tmp)->next == NULL || (*tmp)->next->type == PIPE))
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->prev && (*tmp)->prev->type == PIPE)
		(*new)->infile = "/dev/stdin";
	else if ((*tmp)->next && (*tmp)->next->type == REDIR_IN && (*tmp)->next->next)
	{
		(*new)->infile = (*tmp)->next->next->value;		
	}
	else if ((*tmp)->prev->prev && (*tmp)->prev->prev->type == REDIR_IN && (*tmp)->prev->prev->prev == NULL)
		(*new)->infile = (*tmp)->prev->value;
}

void	get_outfile(t_token **tmp, t_cmd **new)
{
	if ((*tmp)->next != NULL && (*tmp)->next->type == REDIR_OUT)
	{
		(*new)->outfile = ft_strdup((*tmp)->next->next->value);
	}
	else if ((*tmp)->prev == NULL && (*tmp)->next == NULL)
		(*new)->outfile = ft_strdup("/dev/stdout");
	else if ((*tmp)->next != NULL && (*tmp)->next->type == DREDIR_OUT)
		(*new)->outfile = ft_strdup((*tmp)->next->next->value);
	else if ((*tmp)->next == NULL || (*tmp)->next->type == PIPE)
		(*new)->outfile = ft_strdup("/dev/stdout"); //par defaut
	else
		(*new)->outfile = ft_strdup("/dev/stdout");
}

/*void	get_outfile(t_token **tmp, t_cmd **new)
{
	if ((*tmp)->next != NULL && (*tmp)->next->type == REDIR_OUT)
		(*new)->outfile = open((*tmp)->next->next->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*tmp)->prev == NULL && (*tmp)->next == NULL)
		(*new)->outfile = open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if ((*tmp)->next != NULL && (*tmp)->next->type == DREDIR_OUT)
		(*new)->outfile = open((*tmp)->next->next->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if ((*tmp)->next == NULL || (*tmp)->next->type == PIPE)
		(*new)->outfile = open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644); //par defaut
	else
		(*new)->outfile = open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644);
}*/

t_cmd	*make_new_cmd(t_token **tmp, t_shell *shell)
{
	t_cmd	*new;
	t_token	*curr;
	int	i;
	int	count;

	count = 0;
	i = 0;
	curr = *tmp;
	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	if ((*tmp)->next && (*tmp)->next->type == DREDIR_IN)
		get_here_doc(tmp, &new);
	else
		get_infile(tmp, &new);
	get_outfile(tmp, &new);
	printf("make new cmd INFILE : %s\n", new->infile);
	printf("make new cmd OUTFILE :%d\n", new->outfile);
	while (curr)
	{
		count += ft_strlen(curr->value) + 1;
		if (curr->next)
			curr = curr->next;
		else
			break ;
	}
	printf("make new cmd %d size\n", count + 1);
	new->full_cmd = (char **)malloc(sizeof(char *) * count);
	if (!new->full_cmd)
		return (NULL);// car curieusement i + i au lieu de 100 ne voulait pas 
	i = 0;
	while (*tmp && (*tmp)->type == WORD)
	{
		new->full_cmd[i] = ft_strdup(((*tmp)->value));
		if (!new->full_cmd[i])
			return (free_split(new->full_cmd), NULL); //a verifier 
		i++;
		*tmp = (*tmp)->next;
	}
	new->full_cmd[i] = NULL;
	new->full_path = get_full_path(shell, new->full_cmd[0]);
	new->next = NULL;
	new->prev = NULL;
	return (new);
}
