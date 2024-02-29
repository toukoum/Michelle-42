/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_overflow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:50:09 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/29 15:10:00 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long	ft_ll_atoi(const char *str)
{
	long long	n;
	int	sign;

	n = 0;
	sign = 1;
	while (*str && ((*str >= 9 && *str <= 13) || *str == ' '))
		str++;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str && *str >= '0' && *str <= '9')
	{
		n = n * 10 + *str - '0';
		str++;
	}
	return (n * sign);
}

static int	nbr_len(long long n)
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

char	*ft_ll_itoa(long long n)
{
	char	*str;
	int		i;

	if (n == (-9223372036854775807 - 1))
		return (ft_strdup("-9223372036854775808"));
	i = nbr_len(n);
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (str);
	str[i--] = '\0';
	if (n == 0)
		str[i] = '0';
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	while (i >= 0 && n > 0)
	{
		str[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	return (str);
}

bool	ll_has_overflowed(char *str)
{
	long long	n;
	char		*itoa;

	n = ft_ll_atoi(str);
	itoa = ft_ll_itoa(n);
	if (str[0] == '+')
		str++;
	while (*str && *str == '0')
		str++;
	if (!*str)
		return (false);
	if (ft_strcmp(itoa, str))
		return (free(itoa), true);
	free(itoa);
	return (false);
}
