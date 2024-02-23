/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:46:49 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/23 11:47:40 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**delete_open_file(char **cmd, int i)
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
	return (new_cmd);
}

/**
 * cmd => {"echo", "bonjour", ">", "file", ">", "file2", ">"}
 * {"echo", "bonjour", ">", "file"}
 * @param data
 * @return int
 */
char	**redirection(t_data *data)
{
	int			i;
	int			save_stdout;
	t_tmpfile	*temp;

	i = 0;
	if (check_redir_sign(data->cmd))
		return (NULL);
	if (open_heredoc(data))
		return (NULL);
	while (data->cmd[i])
	{
		if (DEBUG)
		{
			save_stdout = dup(STDOUT_FILENO);
			dup2(2, STDOUT_FILENO);
			printf("\n new comand ====== \n");
			for (int j = 0; data->cmd[j]; j++)
			{
				printf("tour [%d]=> cmd[%d]: %s\n", i, j, data->cmd[j]);
			}
			temp = data->tmpfile;
			while (temp)
			{
				printf("temp file %s \n", temp->name);
				temp = temp->next;
			}
			dup2(save_stdout, STDOUT_FILENO);
		}
		if (is_redir_sign(data->cmd[i], ">", 1))
			data->cmd = redirect_add(data->cmd[i + 1], data->cmd, i);
		else if (is_redir_sign(data->cmd[i], ">>", 2))
			data->cmd = redirect_append(data->cmd[i + 1], data->cmd, i);
		else if (is_redir_sign(data->cmd[i], "<", 1))
			data->cmd = redirect_input(data->cmd[i + 1], data->cmd, i);
		else if (is_redir_sign(data->cmd[i], "<<", 2))
			data->cmd = redirect_heredoc(data, i);
		else
			i++;
		if (!data->cmd)
			return (NULL);
	}
	return (data->cmd);
}
