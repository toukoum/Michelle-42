/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:20:53 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/20 18:36:57 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_quote(char c, char *quote)
{
	if (c == '\'' || c == '"')
	{
		if (c == *quote)
			*quote = 0;
		else if (!*quote)
			*quote = c;
		return (*quote);
	}
	return (-1);
}

static int	pipe_count_words(char *input)
{
	int		i;
	int		words;
	char	quote;

	i = 0;
	words = 1;
	quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote == input[i])
				quote = 0;
			else if (!quote)
				quote = input[i];
		}
		if (input[i] == '|' && !quote)
			words++;
		i++;
	}
	return (words);
}

static int	word_size(char *input, int i, char quote)
{
	int	size;

	size = 0;
	while (input[i])
	{
		set_quote(input[i], &quote);
		if (input[i] == '|' && !quote)
			return (size);
		i++;
		size++;
	}
	return (size);
}

static char	*new_word(char *input, int *i, char *quote)
{
	char	*word;
	int		j;

	word = ft_calloc(word_size(input, *i, *quote) + 1, sizeof(char));
	if (!word)
		return (NULL);
	j = 0;
	if (input[*i] == *quote)
		word[j++] = input[(*i)++];
	while (input[*i])
	{
		set_quote(input[*i], quote);
		if (input[*i] == '|' && !*quote)
			return (word);
		word[j++] = input[(*i)++];
	}
	return (word);
}

char	**pipe_split(char *input)
{
	int		i;
	int		j;
	char	**split;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	split = ft_calloc(pipe_count_words(input) + 1, sizeof(char *));
	if (!split)
		return (free(input), NULL);
	while (input[i])
	{
		set_quote(input[i], &quote);
		if (input[i] != '|' && (i == 0 || input[i - 1] == '|'))
		{
			split[j++] = new_word(input, &i, &quote);
			if (!split[j - 1])
				return (free_split(split), free(input), NULL);
		}
		if (input[i])
			i++;
	}
	return (split);
}
