/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:07:31 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/14 15:51:14 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

int	display_env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	return (0);
}

char	*get_var_value(t_env *head, char *name)
{
	while (head)
	{
		if (!ft_strcmp(head->name, name))
			return (head->value);
		head = head->next;
	}
	return ("");
}

int	env_size(t_env *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

char	**env_to_split(t_env *head)
{
	char	**split;
	int		i;
	char	*tmp;

	split = ft_calloc(env_size(head) + 1, sizeof(char **));
	if (!split)
		return (NULL);
	i = 0;
	while (head)
	{
		tmp = ft_strjoin(head->name, "=");
		if (!tmp)
			return (free_split(split), NULL);
		split[i] = ft_strjoin(tmp, head->value);
		free(tmp);
		if (!split[i])
			return (free_split(split), NULL);
		head = head->next;
		i++;
	}
	return (split);
}
