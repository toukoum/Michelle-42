/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 16:12:51 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/14 18:01:41 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <unistd.h>

char	*get_cwd(void)
{
	char	*cwd;
	int		size;

	size = 200;
	cwd = ft_calloc(size, sizeof(char));
	if (!cwd)
		return (NULL);
	while (!getcwd(cwd, size))
	{
		size *= 2;
		free(cwd);
		cwd = ft_calloc(size, sizeof(char));
		if (!cwd)
			return (NULL);
	}
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
