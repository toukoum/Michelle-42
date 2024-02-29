/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_append.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 22:36:48 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/29 22:41:20 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_export_var_name(char *cmd)
{
	char	*name;
	char	*addr;

	addr = ft_strchr(cmd, '+');
	if (!addr)
		addr = ft_strchr(cmd, '=');
	name = ft_substr(cmd, 0, addr - cmd);
	return (name);
}

static int	append(char *name, char *value, t_env *curr)
{
	char	*tmp;

	free(name);
	tmp = curr->value;
	curr->value = ft_strjoin(curr->value, value);
	free(tmp);
	free(value);
	if (!curr->value)
		return (-1);
	return (0);
}

int	append_var_value(char *name, char *value, t_env **env)
{
	t_env	*curr;

	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
			return (append(name, value, curr));
		else if (curr->next == NULL)
		{
			*env = add_env_node(*env, name, value);
			if (!*env)
				return (-1);
			return (0);
		}
		if (!*env)
			return (-1);
		curr = curr->next;
	}
	return (1);
}
