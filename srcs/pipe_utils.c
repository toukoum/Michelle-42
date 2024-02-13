/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:10:55 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/13 12:11:32 by ketrevis         ###   ########.fr       */
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

void	free_pipes(t_data data)
{
	int	i;

	i = 0;
	while (data.pipes[i])
	{
		free(data.pipes[i]);
		i++;
	}
	free(data.pipes);
}

int	**create_pipes(int size)
{
	int	i;
	int	**pipes;

	pipes = ft_calloc(size + 1, sizeof(int *));
	i = 0;
	while (i < size)
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		pipe(pipes[i]);
		i++;
	}
	return (pipes);
}
