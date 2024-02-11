/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:20:06 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/09 18:13:22 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <stdbool.h>
# include "libft.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_data
{
	char	**command;
	char	**env;
	int		pipeline_size;
	int		*pipes;
	int		i;
}	t_data;

enum e_input_parse_ret
{
	EXIT,
	EMPTY_INPUT,
	SUCCESS
};

t_env	*store_env(char **env);
t_env	*add_env_node(t_env *head, char *name, char *value);

void	free_env_list(t_env *env);
void	display_env(t_env *env);
void	input(t_env *env);
void	quit_shell(t_env *env);
void	free_split_split(char ***split);
void	run_command(t_data data);
void	close_pipes(t_data data);

char	*str_replace(char *str, char *old, char *new, int old_index);
char	*get_var_value(t_env *head, char *name);
char	*replace_var_names(char *input, t_env *env);
char	**pipe_split(char *input);
char	**env_to_split(t_env *head);
char	***split_split(char **pipe_split);

int		exec(char ***split_split, t_env *env);
int		set_quote(char c, char *quote);
int		parse_input(char *input, t_env *env);
int		split_split_size(char ***split);

#endif
