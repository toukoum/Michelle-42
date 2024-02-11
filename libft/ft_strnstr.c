/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:33:36 by ketrevis          #+#    #+#             */
/*   Updated: 2023/10/16 19:33:37 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	is_substr(const char *big, const char *little)
{
	size_t	i;

	i = 0;
	while (big[i] && big[i] == little[i])
		i++;
	return (ft_strlen(little) == i);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (*little == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (i + ft_strlen(little) > len)
			return (NULL);
		if (is_substr(&big[i], little))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
