/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:57:42 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/24 13:22:59 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**redirect_add(char *to_open, char **cmd, int i)
{
	int	fd;

	if (check_to_open(to_open))
		return (NULL);
	to_open = remove_quotes(to_open);
	fd = open(to_open, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
		return (free(to_open), err_open_file(to_open));
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		free(to_open);
		perror("Error with dup");
		return (NULL);
	}
	close(fd);
	free(to_open);
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

char	**redirect_heredoc(t_data *data, int i)
{
	int			fd;
	t_tmpfile	*tmp;

	fd = open(data->tmpfile->name, O_RDONLY);
	if (fd == -1)
		return (err_open_file(data->tmpfile->name));
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("Error with dup");
		return (NULL);
	}
	close(fd);
	tmp = data->tmpfile;
	if (data->tmpfile->next)
		data->tmpfile = data->tmpfile->next;
	unlink(tmp->name);
	free(tmp->name);
	free(tmp);
	return (delete_open_file(data->cmd, i));
}
