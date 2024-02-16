/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:44:59 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/16 14:19:40 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_var_name(char *name, t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	curr = *env;
	if (curr && !ft_strcmp(curr->name, name))
	{
		*env = curr->next;
		free(curr->name);
		free(curr->value);
		free(curr);
		return ;
	}
	while (curr)
	{
		if (curr->next && !ft_strcmp(curr->next->name, name))
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
}

int	ft_unset(char **cmd, t_env **env)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		find_var_name(cmd[i], env);
		i++;
	}
	return (0);
}
