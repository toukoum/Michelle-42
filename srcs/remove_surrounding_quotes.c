/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_surrounding_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:01:31 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/21 15:31:49 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *str)
{
	char	*new_str;
	char	quote;
	int		j;
	int		i;

	i = 0;
	j = 0;
	quote = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (set_quote(str[i], &quote) && str[i] != quote)
			new_str[j++] = str[i];
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
		no_surr_quote[i] = remove_quotes(split[i]);
		if (!no_surr_quote[i])
			return (free_split(split), NULL);
		i++;
	}
	return (no_surr_quote);
}
