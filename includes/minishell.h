/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:20:06 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/27 15:40:27 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>

typedef struct s_env
{
	char				*name;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_tmpfile
{
	char				*name;
	struct s_tmpfile	*next;
}						t_tmpfile;
typedef struct s_data
{
	pid_t				save_stdout;
	pid_t				save_stdin;
	t_tmpfile			*tmpfile;
	t_env				*env_list;
	char				**cmd;
	char				**env;
	int					**pipes;
	char				***split;
	int					i;
	int					exit_code;
}						t_data;

// exit return value
# define TOO_MANY_ARGS -4
# define INVALID_ARG -3

// parse_input return value
# define EXIT -2
# define SYNTAX_ERROR -1

// get_cwd action parameter
enum					e_cwd_action
{
	NOTHING,
	UPDATE,
	FREE,
};

# define DEBUG 0

t_env					*store_env(char **env);
t_env					*add_env_node(t_env *head, char *name, char *value);

void					free_env_list(t_env *env);
void					input(t_env **env);
void					quit_shell(t_env *env, unsigned char exit_code);
void					free_split_split(char ***split);
void					close_pipes(t_data data);
void					free_pipes(int **pipes);
void					catch_sigint(int sig);

char					*str_replace(char *str, char *old, char *new,
							int old_index);
char					*get_var_value(t_env *head, char *name);
char					*replace_var_names(char *input, t_env *env,
							unsigned char res);
char					**pipe_split(char *input);
char					**env_to_split(t_env *head);
char					**remove_surrounding_quotes(char **split);
char					***split_split(char **pipe_split);

int						run_command(t_data *data);
int						exec(char ***split_split, t_env **env);
int						set_quote(char c, char *quote);
int						parse_input(char *input, t_env **env, int *res);
int						split_split_size(char ***split);
int						**create_pipes(int size);
int						count_words(char *str);

bool					is_redirector(char c);
bool					space_before(char *str, int i);
bool					is_empty(char *str);

// BUILTIN
char					*static_cwd(int action);
int						builtin(char **cmd, t_env *env);
int						ft_echo(char **cmd);
int						ft_export(char **cmd, t_env **env);
int						display_env(t_env *env);
int						ft_pwd(void);
int						ft_cd(char **cmd, t_env **env);
int						main_process_builtin(char **cmd, t_env **env);
int						set_var(t_env **env, char *name, char *value);
int						ft_unset(char **cmd, t_env **env);
int						ft_exit(char **no_surr_quotes);
int						handle_exit_code(int exit_code);
bool					can_quit_shell(char **cmd, int *exit_code);

int						redirection(t_data *data);
void					ft_free_cmd(char **cmd);
int						check_to_open(char *to_open);
char					*remove_quotes(char *str);
char					**err_open_file(char *to_open);
int						check_redir_sign(char **cmd);
int						is_redir_sign(char *s1, char *s2, size_t len);
int						open_heredoc(t_data *data);
void					child_heredoc_free(t_data *data);
char					*last_tmp_name(t_tmpfile *head);
t_tmpfile				*add_tmpfile_node(t_tmpfile *head);
char					**redirect_append(char *to_open, char **cmd, int i, t_data *data);
char					**redirect_input(char *to_open, char **cmd, int i, t_data *data);
char					**redirect_add(char *to_open, char **cmd, int i, t_data *data);
char					**delete_open_file(char **cmd, int i, t_data *data);
char					**redirect_heredoc(t_data *data, int i);

#endif
