/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:50:34 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/21 10:55:53 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static bool	is_redirector(char c)
{
	return (c == '>' || c == '<');
}

static int	count_words(char *str)
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

static int	word_size(char *input, int i, char quote)
{
	int	size;

	size = 0;
	if (quote)
	{
		i++;
		size++;
	}
	while (input[i])
	{
		set_quote(input[i], &quote);
		if (input[i] == ' ' && !quote)
		{
			return (size);
		}
		i++;
		size++;
	}
	return (size);
}

static char	*stock_redictors(char *str, int *i)
{
	char	*new_str;
	int		j;

	j = *i;
	while (str[j] && is_redirector(str[j]))
		j++;
	new_str = ft_calloc(j + 1, sizeof(char));
	j = 0;
	while (str[*i] && is_redirector(str[*i]))
		new_str[j++] = str[(*i)++];
	return (new_str);
}

static char	*new_word(char *str, int *i, char *quote)
{
	char	*word;
	int		j;

	if (is_redirector(str[*i]))
		return (stock_redictors(str, i));
	if (str[*i] == *quote && str[*i + 1] == *quote)
	{
		*i += 2;
		*quote = 0;
		return (ft_strdup(""));
	}
	word = ft_calloc(word_size(str, *i, *quote) + 1, sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	while (str[*i])
	{
		if (!*quote && (str[*i] == ' ' || is_redirector(str[*i])))
			return (word);
		word[j++] = str[(*i)++];
		set_quote(str[*i], quote);
	}
	return (word);
}

static char	**split_quote(char *str)
{
	char	**split;
	char	quote;
	int		i;
	int		j;

	split = ft_calloc(count_words(str) + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	j = 0;
	quote = 0;
	while (str[i])
	{
		set_quote(str[i], &quote);
		if ((str[i] != ' ' && (i == 0 || str[i - 1] == ' '
				|| is_redirector(str[i - 1]))) || (is_redirector(str[i])
				&& !quote))
		{
			split[j++] = new_word(str, &i, &quote);
			if (!split[j - 1])
				return (free_split(split), NULL);
		}
		if (str[i] && str[i] == ' ')
			i++;
	}
	return (split);
}

char	***split_split(char **pipe_split)
{
	char	***split;
	int		i;

	split = ft_calloc(split_size(pipe_split) + 1, sizeof(char **));
	if (!split)
		return (NULL);
	i = 0;
	while (pipe_split[i])
	{
		split[i] = split_quote(pipe_split[i]);
		if (!split[i])
			return (free_split_split(split), NULL);
		i++;
	}
	if (DEBUG)
	{
		for (int i = 0; split[i]; i++)
			for (int j = 0; split[i][j]; j++)
				printf("split_split[%d][%d]: %s\n", i, j, split[i][j]);
	}
	return (split);
}
