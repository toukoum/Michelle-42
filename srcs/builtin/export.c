/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:58:33 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/28 17:04:53 by ketrevis         ###   ########.fr       */
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

bool	add_empty_node(t_env **env, char *name)
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
	new->name = ft_strdup(name);
	if (!new)
		return (false);
	if (!*env)
		*env = new;
	else
		curr->next = new;
	return (true);
}

static bool	export_valid(char *cmd, t_env **env)
{
	char	*name;
	char	*value;
	char	*tmp;

	if (!ft_strchr(cmd, '='))
	{
		add_empty_node(env, cmd);
		return (true);
	}
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
	tmp = value;
	value = remove_quotes(value);
	free(tmp);
	if (!value)
		return (free(name), false);
	set_var(env, name, value);
	return (true);
}

static int	no_arg_export(t_env *env)
{
	while (env)
	{
		printf("declare -x %s", env->name);
		if (env->value)
			printf("=\"%s\"", env->value);
		printf("\n");
		env = env->next;
	}
	return (0);
}

int	ft_export(char **cmd, t_env **env)
{
	int	i;

	if (!cmd[1])
		return (no_arg_export(*env));
	i = 1;
	while (cmd[i])
	{
		if (!export_valid(cmd[i], env))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(cmd[1], 2);
			ft_putstr_fd("': not a valid identifier \n'", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
