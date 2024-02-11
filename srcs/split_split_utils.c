/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:41:28 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/09 16:41:31 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_split_split(char ***split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free_split(split[i]);
		i++;
	}
	free(split);
}

int	split_split_size(char ***split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i);
}
