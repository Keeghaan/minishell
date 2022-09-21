/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 17:12:44 by jcourtoi          #+#    #+#             */
/*                                                                            */
/*   Updated: 2022/09/19 15:44:57 by nboratko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define N_ARG_ER "numeric argument required"
// Evil shell
// https://korben.info/evil-sh-script-shell-rendrait-fou-nimporte.html

//STRUCTURE ENVP LISTE CHAINEE

extern int	g_return;

typedef struct s_envp
{	
	char			*var;
	char			*values;
	int				exported;
	struct s_envp	*next;
}	t_envp;

// TOKENS

enum	e_tok_type
{
	WORD = -1,
	PIPE = '|',
	HERE_DOC,
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
	enum e_tok_type	type;
	int				quotes;
	int				empty_cmd;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**full_cmd;
	char			*full_path;
	char			*infile;
	char			*outfile;
	int				redir;
	int				empty;
	int				quotes;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_shell
{
	int		infile;
	int		outfile;
	int		std_in;
	int		std_out;
	int		n_cmds;
	int		pipefd[2];
	int		pipe;
	char	*prev_dir;
	char	*next_dir;
	char	cwd[250];
	char	**env;
	t_cmd	*cmds;
	t_envp	*envp;
	t_token	*token;
	pid_t	*pid;
	int		is_running;
	int		ret;
	int		unclosed_q;
	int		cmd_found;
}	t_shell;

// EXPANDER

void	expander(t_token **token, t_envp **env);
void	support_expander(t_token **token, t_envp **env);
char	*expand_env_var(char *val, t_envp **env, int i);
void	final_expansion(t_token **token, int i, char *val);
void	get_global_return(t_token **token);
void	support_expander_bis(t_token **t, char *val, t_envp **en, int *i);

// TOKENS

int		tokenizer(char *line, t_token **token);
void	add_new_token(t_token **token, char *line, int i, int j);
t_token	*make_new_token(char *line, int i, int j);
int		tokenizer_support_func(t_token **token, int i, int *j, char *line);
int		double_quotes_tokens_one(t_token **token, int i, int *j, char *line);
int		double_quotes_tokens_two(t_token **token, int i, int *j, char *line);
int		single_quotes_tokens_one(t_token **token, int i, int *j, char *line);
int		single_quotes_tokens_two(t_token **token, int i, int *j, char *line);
int		dquotes_func(t_token **token, int i, int *j, char *line);
int		squotes_func(t_token **token, int i, int *j, char *line);
void	no_quotes_tokens_one(t_token **token, int i, int *j, char *line);
void	no_quotes_tokens_two(t_token **token, int i, int *j, char *line);
void	noquotes_func(t_token **token, int i, int *j, char *line);
void	get_token_type(t_token **token);
void	free_token(t_token **token);

// ADVANCED TOKENS
void	tokenize_advanced(t_token **token);
void	str_separate(t_token **token, int i, int len);
void	insert_token_list(t_token **token, char *value);
int		ft_iscrochet(char *s, int i);

//ENVP UTILS
t_envp	*make_new_env(char *envp);
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
int		is_a_dir(char *value);
void	pipex_quatro(t_shell *child, char **envp);
void	shell_loop_ter(t_shell *shell, t_token **tok);
int		no_redir(t_token *t);

//SIGNALS
void	signalisation(int child);
void	handle_sigint(int sig);
void	handle_mister_here(int sig);

// MAIN
int		main(int argc, char **argv, char **envp);
void	run_shell(t_envp **env, t_shell *shell);
void	main_shell_loop(t_envp **en, t_shell *sh, t_token **tok);
int		check_argv(int ac, char **av, char **en);

//PARSING
//int	count_tokens(t_token **token);
char	*check_tokens(t_token **t);
int		parse(t_token **token, t_shell *shell);
int		file_or_command(t_token **t);
int		get_cmds(t_token **t, t_cmd **cmd, t_shell *shell);
int		which_case(t_token **token, t_shell *shell);
int		check_cmd(char *token, char **envp);

//CMDS
t_cmd	*make_new_cmd(t_token **tmp, t_shell *shell);
void	get_outfile(t_token **tmp, t_cmd **new);
void	get_infile(t_token **tmp, t_cmd **new);
void	add_new_cmd(t_cmd **cmd, t_token **tmp, t_shell *shell);
int		is_builtin(t_token **tmp);
t_cmd	*make_new_cmd_null(void);
void	add_null_cmd(t_cmd **cmd);

//PATH_UTILS
char	**get_paths(t_shell *shell, char *cmd, t_envp **envp);
char	*get_full_path(t_shell *shell, char *cmd);
char	**get_env(char **envp);

//BUILTINS
int		cd_cmd(t_shell *shell, char *action);

//export
void	export_var(t_shell *shell, t_envp *envp);
int		check_export(char *opt_var, t_shell *shell);
t_envp	*make_exported(char *argv, t_shell *shell);
void	add_exported(t_envp **envp, t_envp *new);
char	*get_var(char *argv);
char	*get_values(char *argv, t_shell *shell);
int		get_cwd(t_shell *shell);
int		get_prev_dir(t_shell *shell, int back);
int		get_next_dir(t_shell *shell, char *dir);
int		is_it_builtin(t_shell *shell, t_cmd *cmd, int active);
void	print_envp(t_envp *envp, t_cmd *cmd);
void	unset_envp(t_shell *shell, char *unset);
void	fake_export(char *cmd, t_shell *shell);

//EXEC
void	run_cmd(t_shell *shell, char **envp);
void	exec_cmd(t_shell *shell, char *path, char **envp);

//EXEC UTILS
int		is_valid_cmd(char *cmd, char **envp);
int		check_path_cmd2(char *cmd);
int		error_msg(t_shell *shell, t_cmd *cmd, char **envp, int msg);
int		cmd_not_fnd(char *path, char **en);

//PIPEX
void	pipex(t_shell *child, char **envp);
void	get_nbr_cmds(t_shell *shell);
void	path_and_cmd(t_shell *child, int index, char **envp);
void	cmd_not_found(t_shell *child);
void	pipex_loop(t_shell *child, int i, char **envp);
void	child_process(t_shell *child, int index, char **envp);
int		double_cmd(t_token **tok, int msg);

//void	execute(char **cmd, char *path, t_shell *child);

//EXIT
void	handle_exit(t_shell *shell, char *buf);
void	free_exit(t_shell *shell, char *buf, int msg);
int		is_exit_valid(t_shell *shell, char *buf);
int		is_exit_alone(char *buf);

//HERE_DOC
int	get_here_doc(t_token **token, t_cmd **new, t_shell *shell, int a);
void	expand_tmp(char **tmp, t_shell *shell, char *delimiter);

//GNL
char	*get_next_line(int fd, int a);

#endif
