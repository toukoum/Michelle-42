/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:25:51 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/28 18:37:06 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmd(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
}

static int	is_forbidden_char(char *str)
{
	int			size_str;
	const char	*forbidden_chars = "><;&()[]${}!.";

	size_str = ft_strlen(str);
	while (*forbidden_chars)
	{
		if (*str == *forbidden_chars && size_str == 1)
			return (1);
		forbidden_chars++;
	}
	while (*str && (*str == '<' || *str == '>'))
		str++;
	if (*str == '\0')
		return (1);
	return (0);
}

int	check_to_open(char *to_open)
{
	if (!to_open || to_open[0] == '\0')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
		return (1);
	}
	if (is_forbidden_char(to_open))
	{
		ft_putstr_fd("bash: syntax error near unexpected token '",
			STDERR_FILENO);
		ft_putchar_fd(to_open[0], STDERR_FILENO);
		if (to_open[1])
			ft_putchar_fd(to_open[1], STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

int	check_redir_sign(char **cmd)
{
	int		len;
	char	*redir_sign;
	int		i;

	i = 0;
	while (cmd[i])
	{
		redir_sign = cmd[i];
		len = ft_strlen(redir_sign);
		if (ft_strlen(redir_sign) >= 1 && (redir_sign[0] == '>'
				|| redir_sign[1] == '<') && (len > 2 || !ft_strcmp(redir_sign,
					"<>") || !ft_strcmp(redir_sign, "><")))
		{
			ft_putstr_fd("bash: syntax error near unexpected token '",
				STDERR_FILENO);
			ft_putchar_fd(redir_sign[0], STDERR_FILENO);
			if (redir_sign[1])
				ft_putchar_fd(redir_sign[1], STDERR_FILENO);
			ft_putstr_fd("'\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (0);
}

char	**err_open_file(char *to_open)
{
	ft_putstr_fd("bash: ", STDERR_FILENO);
	ft_putstr_fd(to_open, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
	free(to_open);
	return (NULL);
}
