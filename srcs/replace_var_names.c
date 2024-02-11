/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_names.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:16:20 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/08 16:01:50 by ketrevis         ###   ########.fr       */
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
		return (NULL);
	str[0] = '$';
	i = 1;
	while (input[i] && (ft_isalnum(input[i]) || input[i] == '_'))
	{
		str[i] = input[i];
		i++;
	}
	return (str);
}

static char	*replace_curr_name(char *input, t_env *env, int *i, char *c)
{
	char	*name;
	char	*value;
	char	*replaced;

	name = extract_var_name(input + *i);
	if (!name)
		return (free(input), NULL);
	value = get_var_value(env, name + 1);
	replaced = str_replace(input, name, value, *i);
	*i = 0;
	*c = 0;
	free(name);
	free(input);
	return (replaced);
}

char	*replace_var_names(char *input, t_env *env)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (c == input[i])
				c = 0;
			else if (!c)
				c = input[i];
		}
		if (input[i] == '$' && c != '\''
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '_'))
		{
			input = replace_curr_name(input, env, &i, &c);
			if (!input || !input[0])
				break ;
		}
		else
			i++;
	}
	return (input);
}
