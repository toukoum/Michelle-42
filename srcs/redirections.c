/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:46:49 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/27 17:09:33 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**delete_open_file(char **cmd, int i, t_data *data)
{
	char	**new_cmd;
	int		size_cmd;
	int		original_index;
	int		new_index;

	original_index = 0;
	new_index = 0;
	size_cmd = 0;
	while (cmd[size_cmd])
		size_cmd++;
	new_cmd = ft_calloc(size_cmd - 1, sizeof(char *));
	if (!new_cmd)
		return (NULL);
	while (original_index < size_cmd)
	{
		if (original_index == i || original_index == i + 1)
		{
			original_index++;
			continue ;
		}
		new_cmd[new_index] = ft_strdup(cmd[original_index]);
		if (!new_cmd[new_index])
			return (NULL);
		original_index++;
		new_index++;
	}
	free_split(data->split[data->i]);
	data->split[data->i] = new_cmd;
	return (new_cmd);
}

/**
 * cmd => {"echo", "bonjour", ">", "file", ">", "file2", ">"}
 * {"echo", "bonjour", ">", "file"}
 * @param data
 * @return int
 */
int	redirection(t_data *data)
{
	int			i;

	i = 0;
	if (check_redir_sign(data->cmd))
		return (2);
	while (data->cmd[i])
	{
		if (is_redir_sign(data->cmd[i], ">", 1))
			data->cmd = redirect_add(data->cmd[i + 1], data->cmd, i, data);
		else if (is_redir_sign(data->cmd[i], ">>", 2))
			data->cmd = redirect_append(data->cmd[i + 1], data->cmd, i, data);
		else if (is_redir_sign(data->cmd[i], "<", 1))
			data->cmd = redirect_input(data->cmd[i + 1], data->cmd, i, data);
		else if (is_redir_sign(data->cmd[i], "<<", 2))
			data->cmd = redirect_heredoc(data, i);
		else
			i++;
		if (!data->cmd)
			return (data->exit_code);
	}
	return (0);
}
