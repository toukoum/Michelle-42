/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:04 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/28 13:20:35 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/wait.h>

static void	child_free(t_data data)
{
	clear_history();
	free_pipes(data.pipes);
	free_split(data.env);
	free_env_list(data.env_list);
	free_split_split(data.split);
	static_cwd(FREE);
	free(data.pids);
	exit(data.i);
}

static t_data	init_data(char **env, t_env *env_list, int size, char ***split)
{
	t_data	data;

	data.split = split;
	data.pipes = create_pipes(size);
	data.env = env;
	data.tmpfile = NULL;
	data.env_list = env_list;
	data.i = 0;
	data.exit_code = 0;
	data.pids = malloc(split_split_size(split) * sizeof(pid_t));
	return (data);
}

static int	wait_childs(t_data data)
{
	int	i;
	int	status;

	close_pipes(data);
	free_pipes(data.pipes);
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (data.split[i])
	{
		waitpid(data.pids[i], &status, 0);
		i++;
	}
	free(data.pids);
	signal(SIGINT, catch_sigint);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status != 131)
			status += 128;
		printf("\n");
		return (status);
	}
	return (0);
}

static int	create_childs(char ***split, char **env, t_env *env_list)
{
	t_data	data;

	data = init_data(env, env_list, split_split_size(split) - 1, split);
	if (!data.pipes || !data.pids)
		return (free(data.pids), -1);
	while (split[data.i])
	{
		data.cmd = split[data.i];
		if (open_heredoc(&data))
			return (-1);
		data.pids[data.i] = fork();
		if (data.pids[data.i] == -1)
			return (free(data.pids), -1);
		if (data.pids[data.i] == 0)
		{
			data.cmd = split[data.i];
			data.i = run_command(&data);
			child_free(data);
		}
		free_tmpfile(data.tmpfile);
		data.tmpfile = NULL;
		data.i++;
	}
	return (wait_childs(data));
}

int	exec(char ***split, t_env **env_list)
{
	char	**env;
	int		status;

	if (!split)
		return (EXIT);
	if (split_split_size(split) == 1)
	{
		status = main_process_builtin(split[0], env_list);
		if (can_quit_shell(split[0], &status))
			return (free_split_split(split), quit_shell(*env_list, status), 0);
		if (status != -1)
			return (free_split_split(split), status);
	}
	env = env_to_split(*env_list);
	status = create_childs(split, env, *env_list);
	if (status == -1)
		return (free_split(env), free_split_split(split), EXIT);
	free_split(env);
	free_split_split(split);
	return (status);
}
