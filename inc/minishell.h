#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# define SH "minishell"

// Evil shell
// https://korben.info/evil-sh-script-shell-rendrait-fou-nimporte.html

//STRUCTURE ENVP LISTE CHAINEE

extern int	g_return;

typedef struct s_envp
{
	int			exported;
	char		*var;
	char		*values;
	struct s_envp	*next;
}		t_envp;

// TOKENS

enum	e_tok_type
{
	WORD = -1, //par defaut
	PIPE = '|',
	HERE_DOC,	//delimiter
	REDIR_IN = '<',
	REDIR_OUT = '>',
	DREDIR_IN,
	DREDIR_OUT,
};

// QUOTES
// dquotes 3
// single quotes 2
// no quotes 1

typedef struct s_token
{
	char			*value;
	enum 	e_tok_type	type;
	int			quotes; // see QUOTES above
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

typedef struct	s_cmd
{
	char	**full_cmd;
	char	*full_path;
	char	*infile;
	char	*outfile;
	int	redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct	s_shell
{
	int	infile;
	int	outfile;
	int	std_in;
	int	std_out;
	int	n_cmds;
	int	pipefd[2];
	int	pipe;
	char	*prev_dir;
	char	*next_dir;
	char	cwd[250];
	char	**env;
	t_cmd	*cmds;
	t_envp	*envp;
	t_token	*token;
	pid_t	*pid;
	int	is_running;
	int	ret;
}	t_shell;

// EXPANDER

void	expander(t_token **token, t_envp **env);
void	support_expander(t_token **token, t_envp **env);
char	*expand_env_var(char *val, t_envp **env, int i);
void	final_expansion(t_token **token, int i, char *val);
void	get_global_return(t_token **token);

// TOKENS

int	tokenizer(char *line, t_token **token, t_envp **env);
void	add_new_token(t_token **token, char *line, int i, int j, int quotes);
t_token	*make_new_token(char *line, int i, int j, int quotes);
int	double_quotes_tokens(t_token **token, int i, int *j, int k, char *line);
int	single_quotes_tokens(t_token **token, int i, int *j, int k, char *line);
void	get_token_type(t_token **token);
void	free_token(t_token **token);

// ADVANCED TOKENS
void	tokenize_advanced(t_token **token);
void	str_separate(t_token **token, int i, int len);
void	insert_token_list(t_token **token, char *value);
int	ft_iscrochet(char *s, int i);

//ENVP UTILS
t_envp *make_new_env(char *envp);
void	add_new_env(t_envp **env, char *envp);
void	envp_to_lst(t_envp **env, char **envp);
void	print(t_envp **env);
void	free_envp(t_envp **envp);
void	remove_env(t_envp **envp, char *var);

//MINI UTILS
void	free_split(char **s);
void	init_shell_struct(t_shell *shell);
void	free_cmds(t_cmd **cmd);
void	rewind_token(t_token **token, int back);
void	rewind_cmd(t_cmd **cmd, int back);
void	init_shell(t_shell *shell);
//SIGNALS
void	signalisation(int child);
void	handle_sigint(int sig);

// MAIN
int	main(int argc, char **argv, char **envp);
void	run_shell(t_envp **env, t_shell *shell, char **envp);
void	main_shell_loop(t_envp **env, t_shell *shell, t_token **token, char **envp);
void	shell_loop_part_two(char *buf, t_shell *shell, t_token **token, char **envp, t_envp **env);
int	check_argv(int ac, char **av, char **en);

//PARSING
//int	count_tokens(t_token **token);
char	*check_tokens(t_token **t);
int	parse(t_token **token, t_shell *shell);
int	file_or_command(t_token **t);
int	get_cmds(t_token **t, t_cmd **cmd, t_shell *shell);

//CMDS
t_cmd	*make_new_cmd(t_token **tmp, t_shell *shell);
void	get_outfile(t_token **tmp, t_cmd **new);
void	get_infile(t_token **tmp, t_cmd **new);
void	add_new_cmd(t_cmd **cmd, t_token **tmp, t_shell *shell);
int	is_builtin(t_token **tmp);

//PATH_UTILS
char	**get_paths(char *cmd, t_envp **envp);
char	*get_full_path(t_shell *shell, char *cmd);
char	**get_env(char **envp);
//BUILTINS
int	cd_cmd(t_shell *shell, char *action);
void	export_var(t_shell *shell, t_envp *envp);
void	check_export(char *opt_var, t_shell *shell);
t_envp	*make_exported(char *argv);
void	add_exported(t_envp **envp, t_envp *new);
int	get_cwd(t_shell *shell);
int	get_prev_dir(t_shell *shell, int back);
int	get_next_dir(t_shell *shell, char *dir);
int	is_it_builtin(t_shell *shell, t_cmd *cmd, int active);
void	print_envp(t_envp *envp);

//EXEC
void	run_cmd(t_shell *shell, char **envp);
void	exec_cmd(t_shell *shell, char *path, char **envp);

//EXEC UTILS
int		is_valid_cmd(char *cmd, char **envp);
int		check_path_cmd2(char *cmd);
int		error_msg(t_shell *shell, t_cmd *cmd, char **envp, int msg);
int		cmd_not_fnd(char *path, char **en);

//PIPEX
void	pipex(t_shell *child);
void	get_nbr_cmds(t_shell *shell);
void	path_and_cmd(t_shell *child, int index);
void	cmd_not_found(char **cmd, char *path, t_shell *child);
void	execute(char **cmd, char *path, t_shell *child);

//EXIT
void	handle_exit(t_shell *shell, char *buf);

//HERE_DOC
void	get_here_doc(t_token **token, t_cmd **new);

#endif
