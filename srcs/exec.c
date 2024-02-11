/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:04 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/09 18:37:39 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	close_pipes(t_data data)
{
	int	i;

	i = 0;
	while (i < data.pipeline_size * 2)
	{
		close(data.pipes[i]);
		i++;
	}
}

static int	*create_pipes(int size)
{
	int	i;
	int	*pipes;

	pipes = ft_calloc(size * 2, sizeof(int));
	i = 0;
	while (i < size * 2)
	{
		pipe(pipes + i);
		i += 2;
	}
	return (pipes);
}

static void	child_free(t_data data, t_env *env_list, char ***split)
{
	clear_history();
	free(data.pipes);
	free_split(data.env);
	free_env_list(env_list);
	free_split_split(split);
}

static t_data	init_data(char **env, int size)
{
	t_data	data;

	data.i = -1;
	data.pipes = create_pipes(size);
	data.env = env;
	data.pipeline_size = size;
	return (data);
}

static int	create_childs(char ***split, char **env, t_env *env_list)
{
	pid_t	pid;
	t_data	data;
	int		i;

	i = 0;
	data = init_data(env, split_split_size(split));
	while (split[i])
	{
		pid = fork();
		if (pid == -1)
			return (0);
		if (pid == 0)
		{
			data.command = split[i];
			data.i = i;
			run_command(data);
			child_free(data, env_list, split);
			exit(0);
		}
		i++;
	}
	close_pipes(data);
	free(data.pipes);
	return (1);
}

static void	wait_childs(char ***split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		waitpid(-1, NULL, 0);
		i++;
	}
}

int	exec(char ***split, t_env *env_list)
{
	char	**env;

	if (!split)
		return (EXIT);
	env = env_to_split(env_list);
	create_childs(split, env, env_list);
	wait_childs(split);
	free_split(env);
	free_split_split(split);
	return (SUCCESS);
}
