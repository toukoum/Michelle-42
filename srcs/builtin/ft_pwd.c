/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:12:51 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/19 11:38:01 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*static_cwd(int action)
{
	static char	*cwd;

	if (action == FREE)
		return (free(cwd), NULL);
	if (!cwd || action == UPDATE)
	{
		free(cwd);
		cwd = getcwd(cwd, 0);
	}
	return (cwd);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = static_cwd(NOTHING);
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
