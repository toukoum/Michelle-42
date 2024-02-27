/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:09:18 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/27 16:37:50 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quit_shell(t_env *env, unsigned char exit_code)
{
	free_env_list(env);
	rl_clear_history();
	static_cwd(FREE);
	exit(exit_code);
}

void	catch_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_parse_res(int *res, char *input, t_env *env)
{
	add_history(input);
	if (*res == SYNTAX_ERROR)
	{
		printf("syntax error\n");
		*res = 1;
	}
	free(input);
	if (*res == EXIT)
		quit_shell(env, 0);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n'
			&& str[i] != '\v' && str[i] != '\f' && str[i] != '\r')
			return (false);
		i++;
	}
	free(str);
	return (true);
}

void	input(t_env **env)
{
	char			*input;
	int				res;

	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
	res = 0;
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
			quit_shell(*env, 0);
		if (is_empty(input))
			continue ;
		res = parse_input(ft_strdup(input), env, &res);
		handle_parse_res(&res, input, *env);
	}
}
