/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:09:43 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/24 12:42:29 by ketrevis         ###   ########.fr       */
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

int	parse_input(char *input, t_env **env, int *res)
{
	int		status;
	char	**split;
	char	***split_arr;

	if (!quote_closed(input))
		return (free(input), SYNTAX_ERROR);
	input = replace_var_names(input, *env, *res);
	if (is_empty(input))
		return (0);
	if (!input)
		return (EXIT);
	split = pipe_split(input);
	free(input);
	if (!split)
		return (EXIT);
	split_arr = split_split(split);
	free_split(split);
	status = exec(split_arr, env);
	if (status == EXIT)
		return (EXIT);
	return (status);
}
