/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:12:51 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/17 00:15:50 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

char	*get_cwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (NULL);
	return (cwd);
}

int	ft_pwd(void)
{
	char	*cwd;

	cwd = get_cwd();
	if (!cwd)
		return (1);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
