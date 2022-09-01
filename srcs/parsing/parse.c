#include "../../inc/minishell.h"

//returns NULL if it worked and the value of the token if error

char	*check_tokens(t_token **t)
{
	t_token	*tmp;
	int	i;

	tmp = *t;
	i = 0;
	while (tmp)
	{
		if (tmp->type == PIPE && i == 0)
			return (tmp->value);
		if (!tmp->next && tmp->type != WORD) // il faut ecrire "newline" comme message d'erreur
			return ("newline");
		if ((tmp->type == REDIR_IN || tmp->type == REDIR_OUT
			|| tmp->type == DREDIR_IN || tmp->type == DREDIR_OUT
			|| tmp->type == PIPE) && tmp->next->type != WORD)
			return (tmp->next->value);
		i++;
		tmp = tmp->next;	
	}
	return (NULL);
}

/* EXEMPLES DES COMMANDES QUI PEUVENT ETRE ENTREES :
   < Makefile cat | wc > out
   cat << lol | wc -l > out
   cat Makefile */

void	get_cmds(t_token **t, t_cmd **cmd, t_shell *shell)
{
	int	i;
	t_token	*tmp;

	i = 0;
	tmp = *t;
	while (tmp)
	{
		if (tmp->type == WORD) // && tmp->prev->type != REDIR_IN) //&& ((tmp->prev != NULL && tmp->prev->type != DREDIR_IN) || tmp->prev == NULL))
		{
			if (i == 0 && tmp->next && (tmp->next->type == WORD || tmp->next->type == REDIR_IN))
			{
				*cmd = make_new_cmd(&tmp, shell);
			}
			else if ( i == 0 && tmp->next && tmp->next->type == DREDIR_IN)
				*cmd = make_new_cmd(&tmp, shell);
			else if (i > 0 && tmp->prev && tmp->prev->type != REDIR_IN && tmp->prev->type != REDIR_OUT) //une commande ne peut jamais suivre une redirection
			{
				if (*cmd)
				{
					add_new_cmd(cmd, &tmp, shell);
				}
				else
				{
					*cmd = make_new_cmd(&tmp, shell);
				}
			}
			else if (i == 0 && tmp->next == NULL) //une seule commande, par exemple env
				*cmd = make_new_cmd(&tmp, shell);
			else if (tmp->next == NULL && tmp->prev->type == REDIR_OUT) // il s'agit de outfile, c'est pas une commande
				break ;
		}
	//	if (tmp->type == PIPE)
	//		shell->pipe = 1;
		if (tmp && tmp->next)
			tmp = tmp->next;
		else
			break ;
		i++;
	}
}

//will return 0 if all went well and 1 if an error occured

int	parse(t_token **token, t_shell *shell)
{
	char	*check;

	check = check_tokens(token);
	if (check)
	{
		ft_printf("minishell: syntax error near unexpected token `%s'\n", check);
		return (1);
	}
	get_cmds(token, &shell->cmds, shell);
	return (0);
}
