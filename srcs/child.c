/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:48:44 by ketrevis          #+#    #+#             */
/*   Updated: 2024/03/05 14:14:44 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <signal.h>

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

static char	*find_path(t_data data, char **no_quote)
{
	char	*path;
	char	**split;
	int		i;

	path = get_var_value(data.env_list, "PATH");
	split = split_add_slashes(path);
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		path = ft_strjoin(split[i], no_quote[0]);
		if (!path)
			return (NULL);
		if (!access(path, X_OK))
			return (free_split(split), path);
		free(path);
		i++;
	}
	free_split(split);
	if (!is_folder(no_quote[0]) && !access(no_quote[0], X_OK))
		return (no_quote[0]);
	return (NULL);
}

static int	cmd_not_found(char **cmd, int err)
{
	if ((cmd[0][0] == '/' || cmd[0][0] == '.') && access(cmd[0], F_OK))
	{
		ft_putstr_fd("no such file or directory: ", 2);
		err = 127;
	}
	else if ((cmd[0][0] == '/' || cmd[0][0] == '.') && is_folder(cmd[0]))
	{
		ft_putstr_fd("Is a directory: ", 2);
		err = 126;
	}
	else if ((cmd[0][0] == '/' || cmd[0][0] == '.') && access(cmd[0], X_OK))
	{
		ft_putstr_fd("permission denied: ", 2);
		err = 126;
	}
	else
	{
		ft_putstr_fd("command not found: ", 2);
		err = 127;
	}
	return (ft_putstr_fd(cmd[0], 2), ft_putstr_fd("\n", 2), free_split(cmd),
		err);
}

int	execve_error(char *name)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(": permission denied\n", 2);
	return (126);
}

int	run_command(t_data *data, char *input)
{
	char	**no_surr_quotes;
	char	*path;
	int		err;

	signal(SIGQUIT, SIG_DFL);
	setup_pipes(*data, input);
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
	path = find_path(*data, no_surr_quotes);
	if (!path)
		return (cmd_not_found(no_surr_quotes, 0));
	if (execve(path, no_surr_quotes, data->env) == -1)
		err = execve_error(no_surr_quotes[0]);
	if (ft_strcmp(path, data->cmd[0]))
		free(path);
	return (free_split(no_surr_quotes), err);
}
