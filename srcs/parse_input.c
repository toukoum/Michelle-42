/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:09:43 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/29 12:14:01 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	quote_closed(char *input)
{
	int	s_count;
	int	d_count;
	int	i;

	s_count = 0;
	d_count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\'' && d_count % 2 == 0)
			s_count++;
		if (input[i] == '"' && s_count % 2 == 0)
			d_count++;
		i++;
	}
	return (s_count % 2 == 0 && d_count % 2 == 0);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

static bool	is_valid_command(char *str, int *i, char *quote)
{
	(*i)++;
	if (str[*i] == '|')
		return (false);
	while (str[*i])
	{
		set_quote(str[*i], quote);
		if (str[*i] == '|' && !*quote)
			return (false);
		if (!is_whitespace(str[*i]))
			return (true);
		(*i)++;
	}
	return (false);
}

bool	pipe_valid(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i])
	{
		set_quote(str[i], &quote);
		if (str[i] == '|' && !quote)
		{
			if (!is_valid_command(str, &i, &quote))
			{
				ft_putstr_fd("syntax error\n", 2);
				return (false);
			}
		}
		i++;
	}
	return (true);
}

int	parse_input(char *input, t_env **env, int *res)
{
	int		status;
	char	**split;
	char	***split_arr;

	if (!pipe_valid(input))
		return (1);
	if (!quote_closed(input))
		return (free(input), SYNTAX_ERROR);
	input = replace_var_names(input, *env, *res);
	if (is_empty(input))
		return (0);
	if (!input)
		return (EXIT);
	split = pipe_split(input);
	if (!split)
		return (EXIT);
	split_arr = split_split(split);
	free_split(split);
	free(input);
	status = exec(split_arr, env);
	if (status == EXIT)
		return (EXIT);
	return (status);
}
