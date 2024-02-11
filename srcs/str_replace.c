/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:32:02 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/07 11:32:39 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_replace(char *str, char *old, char *new, int old_index)
{
	char	*new_str;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(str) + ft_strlen(new) - ft_strlen(old);
	new_str = ft_calloc(size + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] && j <= size)
	{
		if (!ft_strncmp(str + i, old, ft_strlen(old)) && i == old_index)
		{
			j += ft_strlcpy(new_str + j, new, ft_strlen(new) + 1);
			ft_strlcpy(new_str + j, str + i + ft_strlen(old), ft_strlen(str));
			return (new_str);
		}
		new_str[j++] = str[i++];
	}
	return (new_str);
}
