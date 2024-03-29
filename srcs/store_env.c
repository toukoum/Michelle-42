/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:50:43 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/29 19:32:40 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_env	*basic_env(void)
{
	t_env	*env;

	env = NULL;
	env = add_env_node(env, ft_strdup("PWD"), ft_strdup(static_cwd(NOTHING)));
	env = add_env_node(env, ft_strdup("SHLVL"), ft_itoa(1));
	env = add_env_node(env, ft_strdup("_"), ft_strdup("/usr/bin/env"));
	return (env);
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
	if (!env[0])
		return (basic_env());
	while (env[i])
	{
		env_list = add_env_node(env_list, get_env_var_name(env[i]),
				get_env_var_value(env[i]));
		if (!env_list)
			return (free_env_list(env_list), NULL);
		i++;
	}
	return (env_list);
}

static char	*increment_shlvl(char *name, char *value)
{
	int	n;

	if (ft_strcmp(name, "SHLVL"))
		return (value);
	n = ft_atoi(value) + 1;
	free(value);
	value = ft_itoa(n);
	return (value);
}

t_env	*add_env_node(t_env *head, char *name, char *value)
{
	t_env	*new;
	t_env	*curr;

	curr = head;
	if (!name || !value)
		return (free(name), free(value), free_env_list(head), NULL);
	value = increment_shlvl(name, value);
	if (!value)
		return (free(name), free_env_list(head), NULL);
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
