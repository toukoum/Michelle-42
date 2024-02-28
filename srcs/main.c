/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:50:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/28 15:57:17 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;

	(void)ac;
	(void)av;
	g_exit_code = 0;
	env_list = NULL;
	env_list = store_env(env);
	if (!env_list)
		return (0);
	input(&env_list);
	free_env_list(env_list);
	return (0);
}
