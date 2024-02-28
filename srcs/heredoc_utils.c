/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:02:48 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/28 12:12:47 by rgiraud          ###   ########.fr       */
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
	free(data->pids);
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
	if (!name)
		return (NULL);
	name[9] = '\0';
	fd = open("/dev/urandom", O_RDONLY);
	if (fd == -1)
		return (perror("Failed to open /dev/urandom"), free(name), NULL);
	if (read(fd, name, 9) == -1)
		return (perror("Failed to read from: /dev/urandom"), free(name),
			close(fd), NULL);
	tmp = name;
	while (*tmp)
	{
		*tmp = (*tmp % 26) + 'a';
		tmp++;
	}
	tmp = name;
	name = ft_strjoin("/tmp/", name);
	free(tmp);
	dprintf(2, "nom du fichier: %s\n", name);
	return (close(fd), name);
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
	while (!access(new->name, F_OK))
	{
		free(new->name);
		new->name = get_tmp_name();
	}
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
