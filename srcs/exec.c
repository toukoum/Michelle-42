/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 13:10:04 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/23 12:28:32 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <sys/wait.h>

static void	child_free(t_data data, t_env *env_list, char ***split)
{
	clear_history();
	free_pipes(data.pipes);
	free_split(data.env);
	free_env_list(env_list);
	free_split_split(split);
	static_cwd(FREE);
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
	return (data);
}

static int	create_childs(char ***split, char **env, t_env *env_list)
{
	pid_t	pid;
	t_data	data;

	data.i = 0;
	data = init_data(env, env_list, split_split_size(split) - 1, split);
	if (!data.pipes)
		return (-1);
	while (split[data.i])
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		if (pid == 0)
		{
			data.cmd = split[data.i];
			data.i = run_command(data);
      dup2(data.save_stdout, STDOUT_FILENO);
			dup2(data.save_stdin, STDIN_FILENO);
			child_free(data, env_list, split);
			exit(data.i);
		}
		data.i++;
	}
	close_pipes(data);
	free_pipes(data.pipes);
	return (1);
}

static int	wait_childs(char ***split)
{
	int	i;
	int	status;

	i = 0;
	signal(SIGINT, SIG_IGN);
	while (split[i])
	{
		waitpid(-1, &status, 0);
		i++;
	}
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

int	exec(char ***split, t_env **env_list)
{
	char	**env;
	int		status;

	if (!split)
		return (EXIT);
	if (split_split_size(split) == 0 || split[0][0] == NULL)
	{
		printf("syntax error near unexpected token '|'\n");
		return (free_split_split(split), 2);
	}
	if (split_split_size(split) == 1)
	{
		status = main_process_builtin(split[0], env_list);
		if (can_quit_shell(split[0], &status))
			return (free_split_split(split), quit_shell(*env_list, status), 0);
		if (status != -1)
			return (free_split_split(split), status);
	}
	env = env_to_split(*env_list);
	if (create_childs(split, env, *env_list) == -1)
		return (free_split(env), free_split_split(split), EXIT);
	status = wait_childs(split);
	free_split(env);
	free_split_split(split);
	return (status);
}
