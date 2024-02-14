	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:58:33 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/13 19:35:31 by ketrevis         ###   ########.fr       */
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

static void	set_var(t_env *env, char *name, char *value)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			free(curr->value);
			free(name);
			curr->value = value;
			return ;
		}
		curr = curr->next;
	}
	add_env_node(env, name, value);
}

static bool	export_valid(char **cmd, t_env *env)
{
	char	*name;
	char	*value;

	if (!ft_strchr(cmd[1], '='))
		return (false);
	name = ft_substr(cmd[1], 0, ft_strchr(cmd[1], '=') - cmd[1]);
	if (!name)
		return (NULL);
	if (!var_name_valid(name))
		return (free(name), false);
	value = ft_substr(cmd[1], ft_strchr(cmd[1], '=') - cmd[1] + 1, ft_strlen(cmd[1]));
	if (!value)
		return (free(name), false);
	set_var(env, name, value);
	return (true);
}

int	ft_export(char **cmd, t_env *env)
{
	if (!export_valid(cmd, env))
		return (1);
	return (1);
}
