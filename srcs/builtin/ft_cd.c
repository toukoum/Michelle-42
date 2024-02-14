/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:11:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/14 18:05:07 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

int	ft_cd(char **cmd, t_env *env)
{
	char	*export_cmd[2];
	char	*cwd;

	cwd = get_cwd();
	if (chdir(cmd[1]) == -1)
	{
		printf("no such file or directory %s\n", cmd[1]);
		return (1);
	}
	export_cmd[0] = "export";
	export_cmd[1] = ft_strjoin("OLDPWD=", cwd);
	ft_export(export_cmd, env);
	free(cwd);
	free(export_cmd[1]);
	cwd = get_cwd();
	if (!cwd)
		return (1);
	export_cmd[1] = ft_strjoin("PWD=", cwd);
	ft_export(export_cmd, env);
	free(cwd);
	free(export_cmd[1]);
	return (0);
}
