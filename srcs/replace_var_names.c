/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_names.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:16:20 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/29 14:36:06 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static char	*extract_var_name(char *input)
{
	char	*str;
	int		i;

	i = 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (free(input), NULL);
	str[0] = '$';
	i = 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
		str[i] = input[i];
		i++;
	}
	return (str);
}

static char	*replace_curr_name(char *input, t_env *env, int *i,
		unsigned char res)
{
	char	*name;
	char	*value;
	char	*replaced;

	if (input[*i] == '$' && input[*i + 1] == '?')
	{
		value = ft_itoa(res);
		replaced = str_replace(input, "$?", value, *i);
		free(value);
		free(input);
		return (replaced);
	}
	name = extract_var_name(input + *i);
	if (!name)
		return (free(input), NULL);
	value = get_var_value(env, name + 1);
	replaced = str_replace(input, name, value, *i);
	*i = 0;
	free(name);
	free(input);
	return (replaced);
}

bool	is_limiter(char *str, int i, char quote)
{
	int	counter;

	counter = 0;
	if (quote)
		return (false);
	while (i >= 0 && is_whitespace(str[i]))
		i--;
	if (i == 0 || str[i - 1] != '<')
		return (false);
	i--;
	while (i >= 0 && str[i] == '<')
	{
		counter++;
		i--;
	}
	return (counter == 2);
}

static int	is_var_name_start(char *input, int i, char *quote)
{
	if (*quote == '\'')
		return (0);
	if (!is_limiter(input, i, *quote) && input[i] == '$' && (ft_isalnum(input[i + 1])
			|| input[i + 1] == '_'))
	{
		*quote = 0;
		return (1);
	}
	if (!is_limiter(input, i, *quote) && input[i] == '$' && input[i + 1] == '?')
	{
		*quote = 0;
		return (1);
	}
	return (0);
}

char	*replace_var_names(char *input, t_env *env, unsigned char res)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		set_quote(input[i], &quote);
		if (is_var_name_start(input, i, &quote))
		{
			input = replace_curr_name(input, env, &i, res);
			if (!input || !input[0])
				break ;
		}
		else
			i++;
	}
	return (input);
}
