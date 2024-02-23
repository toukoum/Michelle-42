/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:58:33 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/21 17:20:53 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static bool	var_name_valid(char *name)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

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

static bool	export_valid(char *cmd, t_env **env)
{
	char	*name;
	char	*value;

	if (!ft_strchr(cmd, '='))
		return (false);
	if (cmd[0] == '=')
		return (false);
	name = ft_substr(cmd, 0, ft_strchr(cmd, '=') - cmd);
	if (!name)
		return (NULL);
	if (!var_name_valid(name))
		return (free(name), false);
	value = ft_substr(cmd, ft_strchr(cmd, '=')
			- cmd + 1, ft_strlen(cmd));
	if (!value)
		return (free(name), false);
	set_var(env, name, value);
	return (true);
}

int	ft_export(char **cmd, t_env **env)
{
	int	i;

	if (!cmd[1])
		return (1);
	i = 1;
	while (cmd[i])
	{
		if (!export_valid(cmd[i], env))
		{
			printf("export: `%s': not a valid identifier\n", cmd[1]);
			return (1);
		}
		i++;
	}
	return (0);
}
