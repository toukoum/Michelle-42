/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:29:22 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/27 17:46:46 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

int	builtin(char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd));
	if (!ft_strcmp(cmd[0], "env"))
		return (display_env(env));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, &env));
	if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, &env));
	if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, &env));
	if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd));
	return (-1);
}

int	main_process_builtin(char **cmd, t_env **env)
{
	char	**no_surr_quotes;
	int		status;

	status = -1;
	no_surr_quotes = remove_surrounding_quotes(cmd);
	if (!no_surr_quotes)
		return (EXIT);
	if (!ft_strcmp(no_surr_quotes[0], "cd"))
		status = ft_cd(cmd, env);
	else if (!ft_strcmp(no_surr_quotes[0], "export"))
		status = ft_export(cmd, env);
	else if (!ft_strcmp(no_surr_quotes[0], "unset"))
		status = ft_unset(cmd, env);
	else if (!ft_strcmp(no_surr_quotes[0], "exit"))
		status = ft_exit(no_surr_quotes);
	free_split(no_surr_quotes);
	return (status);
}
