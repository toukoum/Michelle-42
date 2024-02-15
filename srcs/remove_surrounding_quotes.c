/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_surrounding_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:01:31 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/15 14:01:38 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*remove_last_quote(char *str, char quote)
{
	char	*new_str;
	int		j;
	int		i;

	i = 0;
	j = 0;
	new_str = ft_calloc(ft_strlen(str), sizeof(char));
	while (str[i])
	{
		if (str[i] != quote)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	return (new_str);
}

char	**remove_surrounding_quotes(char **split)
{
	char	**no_surr_quote;
	int		i;

	no_surr_quote = ft_calloc(split_size(split) + 1, sizeof(char *));
	if (!no_surr_quote)
		return (NULL);
	i = 0;
	while (split[i])
	{
		if (split[i][0] == '"' || split[i][0] == '\'')
			no_surr_quote[i] = remove_last_quote(split[i], split[i][0]);
		else
			no_surr_quote[i] = ft_strdup(split[i]);
		i++;
	}
	return (no_surr_quote);
}
