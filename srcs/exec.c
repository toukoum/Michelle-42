/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:04 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/13 19:36:39 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/wait.h>

static void	child_free(t_data data, t_env *env_list, char ***split)
{
	clear_history();
	free_pipes(data);
	free_split(data.env);
	free_env_list(env_list);
	free_split_split(split);
}

static t_data	init_data(char **env, t_env *env_list, int size)
{
	t_data	data;

	data.pipes = create_pipes(size);
	data.env = env;
	data.env_list = env_list;
	return (data);
}

static int	create_childs(char ***split, char **env, t_env *env_list)
{
	pid_t	pid;
	t_data	data;
	int		i;

	i = 0;
	data = init_data(env, env_list, split_split_size(split) - 1);
	while (split[i])
	{
		pid = fork();
		if (pid == -1)
			return (0);
		if (pid == 0)
		{
			data.cmd = split[i];
			data.i = i;
			run_command(data);
			child_free(data, env_list, split);
			exit(127);
		}
		i++;
	}
	close_pipes(data);
	free_pipes(data);
	return (1);
}

static int	wait_childs(char ***split)
{
	int	i;
	int	status;

	i = 0;
	while (split[i])
	{
		waitpid(-1, &status, 0);
		i++;
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	exec(char ***split, t_env *env_list)
{
	char	**env;
	int		status;

	if (!split)
		return (EXIT);
	env = env_to_split(env_list);
	create_childs(split, env, env_list);
	status = wait_childs(split);
	free_split(env);
	free_split_split(split);
	return (status);
}
