/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:20:06 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/20 10:24:54 by rgiraud          ###   ########.fr       */
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

typedef struct s_data
{
	pid_t				save_stdout;
	t_env				*env_list;
	char				**cmd;
	char				**env;
	int					**pipes;
	int					i;
}						t_data;

typedef struct s_redirect
{
	char				*value;
	int					type;
	struct s_redirect	*next;
}						t_redirect;

enum					e_input_parse_ret
{
	SYNTAX_ERROR = -3,
	EMPTY_INPUT = -2,
	EXIT = -1,
};

t_env					*store_env(char **env);
t_env					*add_env_node(t_env *head, char *name, char *value);

void					free_env_list(t_env *env);
void					input(t_env **env);
void					quit_shell(t_env *env);
void					free_split_split(char ***split);
void					close_pipes(t_data data);
void					free_pipes(t_data data);

char					*str_replace(char *str, char *old, char *new,
							int old_index);
char					*get_var_value(t_env *head, char *name);
char					*replace_var_names(char *input, t_env *env, int res);
char					**pipe_split(char *input);
char					**env_to_split(t_env *head);
char					**remove_surrounding_quotes(char **split);
char					***split_split(char **pipe_split);

int						run_command(t_data data);
int						exec(char ***split_split, t_env **env);
int						set_quote(char c, char *quote);
int						parse_input(char *input, t_env **env, int res);
int						split_split_size(char ***split);
int						**create_pipes(int size);

// BUILTIN
char					*get_cwd(void);
int						builtin(char **cmd, t_env *env);
int						ft_echo(char **cmd);
int						ft_export(char **cmd, t_env **env);
int						display_env(t_env *env);
int						ft_pwd(void);
int						ft_cd(char **cmd, t_env **env);
int						main_process_builtin(char **cmd, t_env **env);
int						set_var(t_env **env, char *name, char *value);
int						ft_unset(char **cmd, t_env **env);

int						redirection(t_data *data);
#endif
