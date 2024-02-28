/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 14:18:04 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/28 18:30:36 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_code;

void	heredoc_sigint(int code)
{
	(void)code;
	g_exit_code = 13;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

bool	is_folder(char *name)
{
	struct stat	s_stat;

	return (stat(name, &s_stat) == 0 && S_ISDIR(s_stat.st_mode));
}
