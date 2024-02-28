/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:19:15 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/28 13:22:16 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir_sign(char *s1, char *s2, size_t len)
{
	return (!ft_strcmp(s1, s2) && (ft_strlen(s1) == len));
}

int	child_heredoc(t_data *data, char *delimiteur)
{
	char	*buf;
	int		fd_tmp_file;

	fd_tmp_file = open(last_tmp_name(data->tmpfile),
			O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd_tmp_file == -1)
	{
		perror("Error with open");
		return (1);
	}
	buf = readline(">>> ");
	while (1)
	{
		if (ft_strcmp(buf, delimiteur) == 0)
			break ;
		write(fd_tmp_file, buf, ft_strlen(buf));
		write(fd_tmp_file, "\n", 1);
		free(buf);
		buf = readline(">>> ");
	}
	free(buf);
	close(fd_tmp_file);
	return (0);
}

int	handle_heredoc(t_data *data, int i)
{
	int	pid_fork;
	int	status;

	if (check_to_open(data->cmd[i + 1]))
		return (1);
	pid_fork = fork();
	if (pid_fork == -1)
		return (1);
	else if (pid_fork == 0)
	{
		close_pipes(*data);
		child_heredoc(data, data->cmd[i + 1]);
		child_heredoc_free(data);
		exit(0);
	}
	waitpid(-1, &status, 0);
	// TODO signaux
	return (0);
}

/**
 * data->cmd = {"cat << eof1 < file << eof2"}
 *
 * @param data
 * @return int
 */
int	open_heredoc(t_data *data)
{
	int i;

	i = 0;
	while (data->cmd[i])
	{
		if (is_redir_sign(data->cmd[i], "<<", 2))
		{
			data->tmpfile = add_tmpfile_node(data->tmpfile);
			if (!data->tmpfile || handle_heredoc(data, i))
				return (1);
		}
		i++;
	}
	return (0);
}
