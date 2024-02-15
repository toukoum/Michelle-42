/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 14:44:59 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/15 16:31:03 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_var_name(char *name, t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	curr = *env;
	while (curr)
	{
		tmp = curr;
		if (!ft_strcmp(curr->name, name))
		{
			tmp->next = curr->next;
			if (curr == *env)
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
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
