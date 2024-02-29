/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 22:09:18 by ketrevis          #+#    #+#             */
/*   Updated: 2024/02/29 14:10:10 by ketrevis         ###   ########.fr       */
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
	g_exit_code = CTRL_C;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_parse_res(int *res, char *input, t_env *env)
{
	add_history(input);
	free(input);
	if (*res == 131)
		ft_putstr_fd("Quit (core dumped)\n", 2);
	else if (*res == 139)
		ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
	else if (*res == EXIT)
		quit_shell(env, 0);
}

bool	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (false);
		i++;
	}
	free(str);
	return (true);
}

/**
 * @brief handle the input of user
 * 
 * @param env environement variable
 */
void	input(t_env **env)
{
	char			*input;
	int				res;

	signal(SIGINT, catch_sigint);
	signal(SIGQUIT, SIG_IGN);
	res = 0;
	while (1)
	{
		input = readline(BMAG"🧓 Michelle" COLOR_RESET BHYEL"->"COLOR_RESET" ");
		if (!input)
			quit_shell(*env, 0);
		if (is_empty(input))
			continue ;
		if (g_exit_code == CTRL_C)
		{
			res = 130;
			g_exit_code = 0;
		}
		res = parse_input(ft_strdup(input), env, &res);
		handle_parse_res(&res, input, *env);
	}
}
