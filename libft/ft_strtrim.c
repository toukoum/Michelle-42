/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:12:02 by ketrevis          #+#    #+#             */
/*   Updated: 2023/11/10 11:14:34 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_set(char const c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static size_t	get_size(char const *s1, char const *set)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s1[i] && in_set(s1[i], set))
	{
		i++;
		size++;
	}
	i = ft_strlen(s1) - 1;
	while (i >= 0 && in_set(s1[i], set))
	{
		i--;
		size++;
	}
	return (ft_strlen(s1) - size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		k;
	int		size;

	size = get_size(s1, set) + 1;
	if (size <= 0)
		size = 1;
	str = malloc(size * sizeof(char));
	if (!str)
		return (str);
	i = ft_strlen(s1) - 1;
	j = 0;
	k = 0;
	while (s1[j] && in_set(s1[j], set))
		j++;
	while (i >= 0 && in_set(s1[i], set))
		i--;
	while (j <= i)
		str[k++] = s1[j++];
	str[k] = '\0';
	return (str);
}
