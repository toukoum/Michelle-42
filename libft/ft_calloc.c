/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:27:43 by ketrevis          #+#    #+#             */
/*   Updated: 2023/11/10 11:15:56 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (count == 0 || size == 0)
		return (malloc(0));
	if (count * size < size || count * size < count)
		return (NULL);
	ptr = malloc(count * size);
	if (!ptr)
		return (ptr);
	while (i < count * size)
		ptr[i++] = 0;
	return (ptr);
}
