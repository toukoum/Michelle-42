/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 18:58:40 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/29 22:48:56 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_var(t_env **env, char *name, char *value)
{
	t_env	*curr;

	curr = *env;
	if (!name)
		return (1);
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			free(curr->value);
			free(name);
			curr->value = value;
			return (0);
		}
		curr = curr->next;
	}
	*env = add_env_node(*env, name, value);
	return (0);
}

t_env	*add_empty_node(t_env **env, char *name)
{
	t_env	*curr;
	t_env	*new;

	curr = *env;
	while (curr->next)
	{
		if (!ft_strcmp(curr->name, name))
			return (false);
		curr = curr->next;
	}
	new = ft_calloc(1, sizeof(t_env));
	if (!new)
		return (free_env_list(*env), NULL);
	new->name = ft_strdup(name);
	if (!new->name)
		return (free_env_list(*env), NULL);
	if (!*env)
		*env = new;
	else
		curr->next = new;
	return (*env);
}

char	*get_env_var_name(char *str)
{
	return (ft_substr(str, 0, ft_strchr(str, '=') - str));
}
