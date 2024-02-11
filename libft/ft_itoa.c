/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 18:14:40 by ketrevis          #+#    #+#             */
/*   Updated: 2023/11/10 11:14:31 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(int n)
{
	int		size;
	long	nb;

	size = 1;
	nb = (long)n;
	if (n < 0)
	{
		nb = -nb;
		size++;
	}
	while (nb >= 10)
	{
		size++;
		nb /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nb;

	i = nbr_len(n);
	nb = (long)n;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (str);
	str[i--] = '\0';
	if (n == 0)
		str[i] = '0';
	if (n < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	while (i >= 0 && nb > 0)
	{
		str[i] = nb % 10 + 48;
		nb /= 10;
		i--;
	}
	return (str);
}
