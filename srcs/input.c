/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:09:18 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/13 16:29:20 by ketrevis         ###   ########.fr       */
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
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_parse_res(int res, char *input, t_env *env)
{
	if (res != EMPTY_INPUT)
		add_history(input);
	if (res == SYNTAX_ERROR)
		printf("syntax error\n");
	free(input);
	if (res == EXIT)
		quit_shell(env);
}

void	input(t_env *env)
{
	char	*input;
	int		res;

	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
	res = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			quit_shell(env);
		res = parse_input(ft_strdup(input), env, res);
		handle_parse_res(res, input, env);
	}
}
