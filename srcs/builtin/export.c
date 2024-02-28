/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 18:58:33 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/28 18:58:58 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static bool	var_name_valid(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (false);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static bool	handle_no_value(char *cmd, t_env **env)
{
	if (!var_name_valid(cmd))
		return (false);
	add_empty_node(env, cmd);
	return (true);
}

static bool	export_valid(char *cmd, t_env **env)
{
	char	*name;
	char	*value;
	char	*tmp;

	if (!ft_strchr(cmd, '='))
		return (handle_no_value(cmd, env));
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
			ft_putstr_fd("': not a valid identifier \n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}
