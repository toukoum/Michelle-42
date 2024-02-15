/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:48:44 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/15 12:56:25 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

static char	*remove_last_quote(char *str, char quote)
{
	char	*new_str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i])
	{
		if (str[i] != quote)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	return (new_str);
}

char	**remove_surrounding_quotes(char **split)
{
	char	**no_surr_quote;
	int		i;

	no_surr_quote = ft_calloc(split_size(split) + 1, sizeof(char *));
	if (!no_surr_quote)
		return (NULL);
	i = 0;
	while (split[i])
	{
		if (split[i][0] == '"' || split[i][0] == '\'')
			no_surr_quote[i] = remove_last_quote(split[i], split[i][0]);
		else
			no_surr_quote[i] = ft_strdup(split[i]);
		i++;
	}
	return (no_surr_quote);
}

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

	if ((data.cmd[0][0] == '/' || data.cmd[0][0] == '.')
		&& !access(data.cmd[0], X_OK))
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

	setup_pipes(data);
	no_surr_quotes = remove_surrounding_quotes(data.cmd);
	if (builtin(no_surr_quotes, data.env_list))
		return (free_split(no_surr_quotes), 1);
	path = find_path(data);
	if (!path)
	{
		printf("command not found: %s\n", no_surr_quotes[0]);
		free_split(no_surr_quotes);
		return (0);
	}
	execve(path, no_surr_quotes, data.env);
	if (ft_strcmp(path, data.cmd[0]))
		free(path);
	free_split(no_surr_quotes);
	return (1);
}
