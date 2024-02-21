/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:10:55 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/20 18:41:40 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_data data)
{
	int	i;

	i = 0;
	while (data.pipes[i])
	{
		close(data.pipes[i][0]);
		close(data.pipes[i][1]);
		i++;
	}
}

void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	while (pipes[i])
	{
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**create_pipes(int size)
{
	int	i;
	int	**pipes;

	pipes = ft_calloc(size + 1, sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < size)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		if (!pipes[i])
			return (free_pipes(pipes), NULL);
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}
