/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 17:46:49 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/20 15:16:30 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/minishell.h"

// int redirect_add(char *cmd_word, char *next_command)
// {
// 	int fd;
// 	char *to_open;
// 	if (cmd_word)
// 		to_open = cmd_word;
// 	else
// 		to_open = next_command;
// 	if (!to_open)
// 		printf("pas de path");
// 	fd = open(to_open, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (fd == -1)
// 	{
// 		perror("pb open");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup");int redirect_add(char *cmd_word, char *next_command)
// {
// 	int fd;
// 	char *to_open;
// 	if (cmd_word)
// 		to_open = cmd_word;
// 	else
// 		to_open = next_command;
// 	if (!to_open)
// 		printf("pas de path");
// 	fd = open(to_open, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (fd == -1)
// 	{
// 		perror("pb open");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup");
// 		return (-1);
// 	}

// 	return (0);
// }

// /**
//  * "bonjour>file>file2"
//  * 
//  * @param cmd_word 
//  * @return int 
//  */
// int split_word_cmd(char *cmd_word, char *next_command)
// {
// 	int i;
// 	char quote;
// 	int err;

// 	quote = 0;
// 	i = 0;
// 	while (cmd_word[i])
// 	{
// 		quote = set_quote(cmd_word[i], quote);
// 		if (!quote)
// 		{
// 			if (cmd_word[i] == '>')
// 				err = redirect_add(cmd_word + i + 1, next_command);
// 		}
// 	}int redirect_add(char *cmd_word, char *next_command)
// {
// 	int fd;
// 	char *to_open;
// 	if (cmd_word)
// 		to_open = cmd_word;
// 	else
// 		to_open = next_command;
// 	if (!to_open)
// 		printf("pas de path");
// 	fd = open(to_open, O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	if (fd == -1)
// 	{
// 		perror("pb open");
// 		return (-1);
// 	}
// 	if (dup2(fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup");
// 		return (-1);
// 	}

// 	return (0);
// }

// /**
//  * "bonjour>file>file2"
//  * 
//  * @param cmd_word 
//  * @return int 
//  */
// int split_word_cmd(char *cmd_word, char *next_command)
// {
// 	int i;
// 	char quote;
// 	int err;

// 	quote = 0;
// 	i = 0;
// 	while (cmd_word[i])
// 	{
// 		quote = set_quote(cmd_word[i], quote);
// 		if (!quote)
// 		{
// 			if (cmd_word[i] == '>')
// 				err = redirect_add(cmd_word + i + 1, next_command);
// 		}
// 	}
// 	return (err);
// }


// t_redirect *parse_redir(t_redirect *redir, t_data *data)
// {
// 	int i;
// 	int err;
	
// 	i = 0;
// 	while (data->cmd[i])
// 	{
// 		printf("cmd[%d]: %s\n", i, data->cmd[i]);
// 		err = split_word_cmd(data->cmd[i], data->cmd[i + 1]);
// 		if (err == -1)
// 			return (NULL);
// 		i++;
// 	}
// 	return (redir);
// }
// 	return (err);
// }


// t_redirect *parse_redir(t_redirect *redir, t_data *data)
// {
// 	int i;
// 	int err;
	
// 	i = 0;
// 	while (data->cmd[i])
// 	{
// 		printf("cmd[%d]: %s\n", i, data->cmd[i]);
// 		err = split_word_cmd(data->cmd[i], data->cmd[i + 1]);
// 		if (err == -1)
// 			return (NULL);
// 		i++;
// 	}
// 	return (redir);
// }
// 		return (-1);
// 	}

// 	return (0);
// }

// /**
//  * "bonjour>file>file2"
//  * 
//  * @param cmd_word 
//  * @return int 
//  */
// int split_word_cmd(char *cmd_word, char *next_command)
// {
// 	int i;
// 	char quote;
// 	int err;

// 	quote = 0;
// 	i = 0;
// 	while (cmd_word[i])
// 	{
// 		quote = set_quote(cmd_word[i], quote);
// 		if (!quote)
// 		{
// 			if (cmd_word[i] == '>')
// 				err = redirect_add(cmd_word + i + 1, next_command);
// 		}
// 	}
// 	return (err);
// }


// t_redirect *parse_redir(t_redirect *redir, t_data *data)
// {
// 	int i;
// 	int err;
	
// 	i = 0;
// 	while (data->cmd[i])
// 	{
// 		printf("cmd[%d]: %s\n", i, data->cmd[i]);
// 		err = split_word_cmd(data->cmd[i], data->cmd[i + 1]);
// 		if (err == -1)
// 			return (NULL);
// 		i++;
// 	}
// 	return (redir);
// }

/**
 * cmd => {"echo", "bonjour", ">", "file", ">", "file2"}	
 * {"echo", "bonjour", ">", "file"}	
 * @param data 
 * @return int 
 */
int		redirection(t_data *data)
{
	// int i;
	// t_redirect redir;
	(void)data;
	return (0);
	// parse_redir(&redir, data);
	
	// make_redir(redir);
	// data->cmd = clear_cmd(data->cmd);
	
	// // printf("bonjour\n");
	// for (int i = 0; data.cmd[i]; i++)
	// {
	// 	if (data.cmd[i] && data.cmd[i][0] == '>')
	// 	{
	// 		printf("redir bonjour dans file\n");
	// 		// // redirection >
	// 		// int fd = open(data.cmd[3], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			
	// 		// // redirection >>
	// 		// int fd = open(data->cmd[3], O_CREAT | O_WRONLY | O_APPEND, 0644);

	// 		// redirection <
	// 		int fd = open(data.cmd[3], O_RDONLY);
			
	// 		//redirection <<
			
	// 		if (fd == -1)
	// 		{
	// 			perror("pb open");
	// 			return (-1);
	// 		}
	// 		dup2(fd, STDOUT_FILENO);
	// 	}
	// }
	return (0);
}

// int main()
// {
// 	char *cmd[] = {"cat", "<", "test>newest", ">" "\"file2>txt\""};
// 	t_data data;

// 	data.cmd = cmd;
// 	redirection(&data);
// 	return 0;
// }
