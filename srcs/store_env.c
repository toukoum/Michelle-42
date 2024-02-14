/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:50:43 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/14 16:07:25 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_var_name(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	new_str = ft_calloc(i + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		new_str[i] = str[i];
		i++;
	}
	return (new_str);
}

static char	*get_env_var_value(char *str)
{
	int		i;
	char	*new_str;

	i = 0;
	while (str[i] != '=')
		i++;
	i++;
	new_str = ft_strdup(str + i);
	return (new_str);
}

/**
 * @brief create a linked list
 * with in each node = name / value
 *
 * @param env list of all environement variable
 * @return t_env* linked list of the env variable
 */
t_env	*store_env(char **env)
{
	t_env	*env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (env[i])
	{
		env_list = add_env_node(env_list, get_env_var_name(env[i]),
				get_env_var_value(env[i]));
		if (!env_list)
			return (NULL);
		i++;
	}
	return (env_list);
}

t_env	*add_env_node(t_env *head, char *name, char *value)
{
	t_env	*new;
	t_env	*curr;

	curr = head;
	if (!name || !value)
		return (free(name), free(value), free_env_list(head), NULL);
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (free(name), free(value), free_env_list(head), NULL);
	new->name = name;
	new->value = value;
	if (!head)
		head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (head);
}
