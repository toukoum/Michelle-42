/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:29:22 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/19 12:30:55 by ketrevis         ###   ########.fr       */
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
		return (quit_shell(env), 0);
	return (-1);
}

int	main_process_builtin(char **cmd, t_env **env)
{
	char	**no_surr_quotes;
	int		status;

	status = -1;
	no_surr_quotes = remove_surrounding_quotes(cmd);
	if (!no_surr_quotes)
		return (-2);
	if (!ft_strcmp(no_surr_quotes[0], "cd"))
		status = ft_cd(cmd, env);
	else if (!ft_strcmp(no_surr_quotes[0], "export"))
		status = ft_export(cmd, env);
	else if (!ft_strcmp(no_surr_quotes[0], "unset"))
		status = ft_unset(cmd, env);
	else if (!ft_strcmp(no_surr_quotes[0], "exit"))
		status = EXIT;
	free_split(no_surr_quotes);
	return (status);
}
