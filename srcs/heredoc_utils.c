/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:02:48 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/23 15:26:24 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tmpfile(t_tmpfile *tmpfile_list)
{
	t_tmpfile	*tmp;

	while (tmpfile_list)
	{
		tmp = tmpfile_list;
		tmpfile_list = tmpfile_list->next;
		free(tmp->name);
		free(tmp);
	}
}

void	child_heredoc_free(t_data *data)
{
	// TODO
	clear_history();
	free_pipes(data->pipes);
	free_split(data->env);
	free_env_list(data->env_list);
	free_split_split(data->split);
	free_tmpfile(data->tmpfile);
	return ;
}

char	*last_tmp_name(t_tmpfile *head)
{
	if (!head)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head->name);
}

char	*get_tmp_name(void)
{
	char	*name;
	char	*tmp;
	int		fd;

	name = malloc(10 * sizeof(char));
	name[9] = '\0';
	if (!name)
		return (NULL);
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open /dev/urandom");
		free(name);
		return (NULL);
	}
	if (read(fd, name, 9) == -1)
	{
		perror("Failed to read from: /dev/urandom");
		return (free(name), close(fd), NULL);
	}
	tmp = name;
	name = ft_strjoin("/tmp/", name);
	free(tmp);
	close(fd);
	return (name);
}

t_tmpfile	*add_tmpfile_node(t_tmpfile *head)
{
	t_tmpfile	*new;
	t_tmpfile	*curr;

	curr = head;
	new = ft_calloc(1, sizeof(t_tmpfile));
	if (!new)
		return (NULL);
	new->name = get_tmp_name();
	if (!new->name)
		return (NULL);
	if (!head)
		head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (head);
}
