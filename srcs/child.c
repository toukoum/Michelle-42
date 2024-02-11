/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:48:44 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/09 18:13:31 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	**remove_surrounding_quotes(char **split)
{
	char	**no_surr_quote;
	int		i;

	no_surr_quote = ft_calloc(split_size(split) + 1, sizeof(char *));
	if (!no_surr_quote)
		return (NULL);
	i = 0;
	while (split[i])
	{
		if (split[i][0] == '"' || split[i][0] == '\'')
			no_surr_quote[i] = ft_substr(split[i], 1, ft_strlen(split[i]) - 2);
		else
			no_surr_quote[i] = ft_strdup(split[i]);
		i++;
	}
	return (no_surr_quote);
}

static void	setup_pipes(t_data data)
{
	if (data.i != data.pipeline_size - 1)
		dup2(data.pipes[1], 1);
	dup2(data.pipes[0], 0);
	close_pipes(data);
}

void	run_command(t_data data)
{
	char	**no_surr_quotes;

	setup_pipes(data);
	if (data.i != data.pipeline_size - 1)
		for (int i = 0; data.command[i]; i++)
			printf("%s\n", data.command[i]);
	no_surr_quotes = remove_surrounding_quotes(data.command);
	if (data.i == data.pipeline_size - 1)
		execve("/usr/bin/grep", no_surr_quotes, data.env);
	free_split(no_surr_quotes);
}
