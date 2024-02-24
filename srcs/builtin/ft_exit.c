/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:51:03 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/24 11:09:06 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

bool	can_quit_shell(char **cmd, int *exit_code)
{
	if (ft_strcmp(cmd[0], "exit"))
		return (false);
	if (*exit_code == TOO_MANY_ARGS)
	{
		*exit_code = 1;
		return (false);
	}
	if (*exit_code == INVALID_ARG)
		*exit_code = 2;
	return (true);
}

static int	get_exit_code(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		i++;
	}
	return ((unsigned char)ft_atoi(str));
}

static int	handle_errors(char **no_surr_quotes, int exit_code)
{
	if (exit_code != -1 && no_surr_quotes[2])
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		return (TOO_MANY_ARGS);
	}
	else if (exit_code == -1)
	{
		ft_putstr_fd("exit\nexit: numeric argument required\n", 2);
		return (INVALID_ARG);
	}
	printf("exit\n");
	return (exit_code);
}

int	ft_exit(char **no_surr_quotes)
{
	int	size;
	int	exit_code;

	size = split_size(no_surr_quotes);
	if (size == 1)
	{
		printf("exit\n");
		return (0);
	}
	exit_code = get_exit_code(no_surr_quotes[1]);
	exit_code = handle_errors(no_surr_quotes, exit_code);
	return (exit_code);
}
