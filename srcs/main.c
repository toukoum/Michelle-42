/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 21:50:45 by ketrevis          #+#    #+#             */
/*   Updated: 2024/03/05 11:58:22 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_prompt(void)
{
	char	*pwd;
	char	*tmp;
	char	*prompt;

	pwd = get_pwd();
	if (!pwd)
		return (ft_strdup("\001\033[33m\033[1m\002> \001\033[0m\002"));
	tmp = pwd;
	prompt = ft_strjoin(pwd, "\001\033[33m\033[1m\002> \001\033[0m\002");
	free(pwd);
	return (prompt);
}

int	main(int ac, char **av, char **env)
{
	t_env	*env_list;
	char	*prompt;

	prompt = NULL;
	(void)ac;
	(void)av;
	g_exit_code = 0;
	env_list = NULL;
	env_list = store_env(env);
	if (!env_list)
		return (0);
	input(&env_list, 0, prompt);
	free_env_list(env_list);
	return (0);
}
