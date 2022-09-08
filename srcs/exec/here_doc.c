#include "../../inc/minishell.h"

static int	write_here_doc(char **tmp, int *file, char *heredoc)
{
	int	cmp;

	//write(1, "> ", 2);
	*tmp = readline("     > ");
	if (!(*tmp))
	{
		printf("YOU MIGHT HAVE A LITTLE HERE DOC PROBLEM\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strlen(*tmp) == ft_strlen(heredoc))
	{
		cmp = ft_strncmp(heredoc, *tmp, ft_strlen(heredoc + 1));
	}
	else
		cmp = 1;
	if (!cmp)
		return (0);
	write(*file, *tmp, ft_strlen(*tmp));
	write(*file, "\n", 1);
	free((*tmp));
	return (1);
}

void	get_here_doc(t_token **token, t_cmd **new)
{
	int		file;
	int		check;
	char	*tmp;

	check = 1;
	file = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		ft_printf("%s\n", strerror(errno));
	while (1)
	{
		check = write_here_doc(&tmp, &file, (*token)->next->next->value);
		if (check == 0)
			break ;
	}
	free(tmp);
	close(file);
	(*new)->infile = (".here_doc");
	/*if ((*new)->infile == -1)
	{
		unlink(".here_doc");
		printf("error\n");
	}*/
}
