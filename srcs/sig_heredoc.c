/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:18:04 by rgiraud           #+#    #+#             */
/*   Updated: 2024/03/05 12:05:20 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_sigint(int code)
{
	(void)code;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_pipes(t_data data, char *input)
{
	free(input);
	if (data.pipes[0] == NULL)
		return ;
	if (data.pipes[data.i] != NULL)
		dup2(data.pipes[data.i][1], 1);
	if (data.i != 0)
		dup2(data.pipes[data.i - 1][0], 0);
	close_pipes(data);
}

bool	is_folder(char *name)
{
	struct stat	s_stat;

	return (stat(name, &s_stat) == 0 && S_ISDIR(s_stat.st_mode));
}
