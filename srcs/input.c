/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:09:18 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/10 10:54:38 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

void	quit_shell(t_env *env)
{
	printf("exit\n");
	free_env_list(env);
	rl_clear_history();
	exit(0);
}

static void	catch_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_parse_res(int res, char *input, t_env *env)
{
	if (res != EMPTY_INPUT)
		add_history(input);
	free(input);
	if (res == EXIT)
		quit_shell(env);
}

void	input(t_env *env)
{
	char	*input;
	int		res;

	(void)res;
	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			quit_shell(env);
		res = parse_input(ft_strdup(input), env);
		handle_parse_res(res, input, env);
	}
}
