/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:11:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/27 19:48:05 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int	update_env(t_env **env, char *old_pwd)
{
	if (!static_cwd(UPDATE))
		return (free(old_pwd), 1);
	if (set_var(env, ft_strdup("OLDPWD"), old_pwd))
		return (1);
	if (set_var(env, getcwd(NULL, 0), ft_strdup("PWD")))
		return (1);
	return (0);
}

static int	no_args(char **cmd, t_env **env, char *old_pwd)
{
	if (!cmd[1])
	{
		if (chdir(get_var_value(*env, "HOME")) == -1)
			return (free(old_pwd), perror(""), 1);
		if (update_env(env, old_pwd))
			return (1);
		return (0);
	}
	return (-1);
}

int	ft_cd(char **cmd, t_env **env)
{
	char	*old_pwd;
	int		res;

	if (split_size(cmd) > 2)
		return (ft_putstr_fd("cd: too many arguments\n", 2), 1);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	res = no_args(cmd, env, old_pwd);
	if (res != -1)
		return (res);
	if (chdir(cmd[1]) == -1)
		return (free(old_pwd), perror(""), 1);
	if (update_env(env, old_pwd))
		return (1);
	return (0);
}
