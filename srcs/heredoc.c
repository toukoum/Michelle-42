/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 10:19:15 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/28 18:41:33 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_redir_sign(char *s1, char *s2, size_t len)
{
	return (!ft_strcmp(s1, s2) && (ft_strlen(s1) == len));
}

void	print_eof_heredoc(char *delimiteur)
{
	ft_putstr_fd("bash: warning: here-document at line 1\
		delimited by end-of-file (wanted `",
		2);
	ft_putstr_fd(delimiteur, 2);
	ft_putstr_fd("')\n", 2);
}

int	child_heredoc(t_data *data, char *delimiteur)
{
	char	*buf;
	int		fd_tmp_file;

	fd_tmp_file = open(last_tmp_name(data->tmpfile),
			O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd_tmp_file == -1)
		return (perror("Error with open"), 1);
	while (1)
	{
		buf = readline(">>> ");
		if (!buf)
			return (close(fd_tmp_file), print_eof_heredoc(delimiteur), 0);
		if (ft_strcmp(buf, delimiteur) == 0)
			break ;
		write(fd_tmp_file, buf, ft_strlen(buf));
		write(fd_tmp_file, "\n", 1);
		free(buf);
	}
	if (buf)
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
	signal(SIGINT, SIG_IGN);
	pid_fork = fork();
	if (pid_fork == -1)
		return (1);
	else if (pid_fork == 0)
	{
		signal(SIGINT, heredoc_sigint);
		signal(SIGQUIT, SIG_IGN);
		close_pipes(*data);
		child_heredoc(data, data->cmd[i + 1]);
		child_heredoc_free(data);
		signal(SIGINT, SIG_DFL);
		exit(0);
	}
	waitpid(-1, &status, 0);
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
	int	i;

	i = 0;
	while (data->cmd[i])
	{
		if (is_redir_sign(data->cmd[i], "<<", 2))
		{
			data->tmpfile = add_tmpfile_node(data->tmpfile);
			if (!data->tmpfile)
				return (1);
			if (handle_heredoc(data, i))
				return (free_tmpfile(data->tmpfile), 1);
		}
		i++;
	}
	return (0);
}
