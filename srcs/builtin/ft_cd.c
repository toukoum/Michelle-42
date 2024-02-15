/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:11:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/15 15:52:13 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ft_cd(char **cmd, t_env **env)
{
	char	*cwd;

	cwd = get_cwd();
	if (!cwd)
		return (1);
	if (chdir(cmd[1]) == -1)
	{
		free(cwd);
		printf("no such file or directory %s\n", cmd[1]);
		return (1);
	}
	if (set_var(env, ft_strdup("OLDPWD"), cwd))
		return (free(cwd), 1);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	if (set_var(env, ft_strdup("PWD"), cwd))
		return (free(cwd), 1);
	return (0);
}
