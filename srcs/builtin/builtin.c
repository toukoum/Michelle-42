/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:29:22 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/13 18:32:32 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin(char **cmd, t_env *env)
{
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd), true);
	if (!ft_strcmp(cmd[0], "env"))
		return (display_env(env), true);
	return (false);
}
