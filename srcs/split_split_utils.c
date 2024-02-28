/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_split_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:41:28 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/28 17:25:43 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirector(char c)
{
	return (c == '<' || c == '>');
}

bool	space_before(char *str, int i)
{
	return (i == 0 || str[i - 1] == ' ');
}

void	free_split_split(char ***split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free_split(split[i]);
		i++;
	}
	free(split);
}

int	split_split_size(char ***split)
{
	int	i;

	i = 0;
	while (split[i] && split[i][0])
		i++;
	return (i);
}

int	count_words(char *str)
{
	int		i;
	int		words;
	char	quote;

	i = 0;
	words = 0;
	quote = 0;
	while (str[i])
	{
		if (set_quote(str[i], &quote) == 0)
			words++;
		if (!quote && ((str[i] != ' ' && (i == 0 || str[i - 1] == ' '
						|| is_redirector(str[i - 1]))) || (is_redirector(str[i])
					&& !is_redirector(str[i - 1]))))
			words++;
		i++;
	}
	return (words);
}
