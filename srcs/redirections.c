/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:46:49 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/21 18:06:32 by rgiraud          ###   ########.fr       */
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

char	**redirect_add(char *to_open, char **cmd, int i)
{
	int	fd;

	if (check_to_open(to_open))
		return (NULL);
	to_open = remove_quotes(to_open);
	fd = open(to_open, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (err_open_file(to_open));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error with dup");
		return (NULL);
	}
	close(fd);
	return (delete_open_file(cmd, i));
}
char	**redirect_input(char *to_open, char **cmd, int i)
{
	int	fd;

	if (check_to_open(to_open))
		return (NULL);
	fd = open(to_open, O_RDONLY);
	if (fd == -1)
		return (err_open_file(to_open));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error with dup");
		return (NULL);
	}
	close(fd);
	return (delete_open_file(cmd, i));
}

char	**redirect_append(char *to_open, char **cmd, int i)
{
	int	fd;

	if (check_to_open(to_open))
		return (NULL);
	fd = open(to_open, O_CREAT | O_APPEND | O_WRONLY, 0644);
	if (fd == -1)
		return (err_open_file(to_open));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("Error with dup");
		return (NULL);
	}
	close(fd);
	return (delete_open_file(cmd, i));
}

/**
 * cmd => {"echo", "bonjour", ">", "file", ">", "file2", ">"}
 * {"echo", "bonjour", ">", "file"}
 * @param data
 * @return int
 */
char	**redirection(t_data *data)
{
	int	i;
	int	save_stdout;

	if (check_redir_sign(data->cmd))
		return (NULL);
	i = 0;
	// open_heredoc(data);
	while (data->cmd[i])
	{
		if (!ft_strcmp(data->cmd[i], ">") && ft_strlen(data->cmd[i]) == 1)
			data->cmd = redirect_add(data->cmd[i + 1], data->cmd, i);
		else if (!ft_strcmp(data->cmd[i], ">>")
			&& ft_strlen(data->cmd[i]) == 2)
			data->cmd = redirect_append(data->cmd[i + 1], data->cmd, i);
		else if (!ft_strcmp(data->cmd[i], "<")
			&& ft_strlen(data->cmd[i]) == 1)
			data->cmd = redirect_input(data->cmd[i + 1], data->cmd, i);
		else
			i++;
		if (!data->cmd)
			return (NULL);	
		if (DEBUG)
		{
			save_stdout = dup(STDOUT_FILENO);
			dup2(2, STDOUT_FILENO);
			printf("\n new comand ====== \n");
			for (int j = 0; data->cmd[j]; j++)
			{
				printf("tour [%d]=> cmd[%d]: %s\n", i, j, data->cmd[j]);
			}
			dup2(save_stdout, STDOUT_FILENO);
		}
	}
	return (data->cmd);
}
// make_redir(redir);
// data->cmd = clear_cmd(data->cmd);

// 		// // redirection >
// 		// int fd = open(data.cmd[3], O_CREAT | O_TRUNC | O_WRONLY, 0644);

// 		// // redirection >>
// 		// int fd = open(data->cmd[3], O_CREAT | O_WRONLY | O_APPEND, 0644);

// 		// redirection <
// 		int fd = open(data.cmd[3], O_RDONLY);

// 		//redirection <<
