/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:11:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/17 00:18:52 by ketrevis         ###   ########.fr       */
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
	if (!cmd[1])
	{
		free(cwd);
		if (chdir(get_var_value(*env, "HOME")) == -1)
			return (perror(""), 1);
		return (0);
	}
	if (chdir(cmd[1]) == -1)
		return (free(cwd), perror(""), 1);
	if (set_var(env, ft_strdup("OLDPWD"), cwd))
		return (free(cwd), 1);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	if (set_var(env, ft_strdup("PWD"), cwd))
		return (free(cwd), 1);
	return (0);
}
