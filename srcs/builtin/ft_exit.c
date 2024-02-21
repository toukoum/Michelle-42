/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:51:03 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/21 14:34:10 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

bool	is_exit_error(int exit_code)
{
	return (exit_code == INVALID_ARG || exit_code == TOO_MANY_ARGS);
}

int	handle_exit_code(int exit_code, char ***split, t_env *env_list)
{
	if (!is_exit_error(exit_code))
		return (exit_code);
	if (exit_code == TOO_MANY_ARGS)
		return (1);
	if (exit_code == INVALID_ARG)
	{
		free_split_split(split);
		free_env_list(env_list);
		static_cwd(FREE);
		exit(2);
	}
	return (0);
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
		printf("exit\nexit: too many arguments\n");
		return (TOO_MANY_ARGS);
	}
	else if (exit_code == -1)
	{
		printf("exit\nexit: numeric argument required\n");
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
