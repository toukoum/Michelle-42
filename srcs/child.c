/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:48:44 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/27 19:39:07 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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

	if ((!access(data.cmd[0], F_OK)))
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

static int	cmd_not_found(char **cmd)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	free_split(cmd);
	return (127);
}

void	execve_error(char *name)
{
	struct stat	s_stat;
	ft_putstr_fd(name, 2);
	if (stat(name, &s_stat) == 0 && S_ISDIR(s_stat.st_mode))
		ft_putstr_fd(": is a directory.\n", 2);
	else
		ft_putstr_fd(": permission denied\n", 2);
}

int	run_command(t_data *data)
{
	char	**no_surr_quotes;
	char	*path;
	int		err;

	setup_pipes(*data);
	if (!data->cmd || !data->cmd[0])
		return (141);
	err = redirection(data);
	if (!data->cmd || !data->cmd[0])
		return (1);
	if (err != 0)
		return (err);
	no_surr_quotes = remove_surrounding_quotes(data->cmd);
	err = builtin(no_surr_quotes, data->env_list);
	if (err != -1)
		return (free_split(no_surr_quotes), err);
	path = find_path(*data);
	if (!path)
		return (cmd_not_found(no_surr_quotes));
	if (execve(path, no_surr_quotes, data->env) == -1)
		execve_error(no_surr_quotes[0]);
	if (ft_strcmp(path, data->cmd[0]))
		free(path);
	free_split(no_surr_quotes);
	return (127);
}
