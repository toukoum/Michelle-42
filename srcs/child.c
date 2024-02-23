/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:48:44 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/23 11:40:38 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_add_slashes(char *path)
{
	int		i;
	char	**split;
	char	*tmp;

	i = 0;
	split = ft_split(path, ':');
	while (split[i])
	{
		if (split[i][ft_strlen(split[i]) - 1] != '/')
		{
			tmp = split[i];
			split[i] = ft_strjoin(split[i], "/");
			free(tmp);
		}
		i++;
	}
	return (split);
}

static char	*find_path(t_data data)
{
	char	*path;
	char	**split;
	int		i;

	if ((!access(data.cmd[0], X_OK)))
		return (data.cmd[0]);
	path = get_var_value(data.env_list, "PATH");
	split = split_add_slashes(path);
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		path = ft_strjoin(split[i], data.cmd[0]);
		if (!path)
			return (NULL);
		if (!access(path, X_OK))
			return (free_split(split), path);
		free(path);
		i++;
	}
	return (free_split(split), NULL);
}

static void	setup_pipes(t_data data)
{
	if (data.pipes[0] == NULL)
		return ;
	if (data.pipes[data.i] != NULL)
		dup2(data.pipes[data.i][1], 1);
	if (data.i != 0)
		dup2(data.pipes[data.i - 1][0], 0);
	close_pipes(data);
}

int	run_command(t_data data)
{
	char	**no_surr_quotes;
	char	*path;
	int		err;

	data.save_stdout = dup(STDOUT_FILENO);
	data.save_stdin = dup(STDIN_FILENO);
	setup_pipes(data);

	data.cmd = redirection(&data);
	no_surr_quotes = remove_surrounding_quotes(data.cmd);
	err = builtin(no_surr_quotes, data.env_list);
	if (err != -1)
		return (free_split(no_surr_quotes), err);
	path = find_path(data);
	if (!path)
	{
		printf("command not found: %s\n", no_surr_quotes[0]);
		free_split(no_surr_quotes);
		return (127);
	}
	if (execve(path, no_surr_quotes, data.env) == -1)
		perror("");
	if (ft_strcmp(path, data.cmd[0]))
		free(path);
	free_split(no_surr_quotes);
	return (127);
}
