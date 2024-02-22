/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiraud <rgiraud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 11:02:48 by rgiraud           #+#    #+#             */
/*   Updated: 2024/02/22 11:25:06 by rgiraud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *get_tmp_name(char *name)
{
	(void)name;
	return ("bonjourat")
}

t_tmpfile *add_tmpfile_node(t_env *head)
{
	t_tmpfile	*new;
	t_tmpfile	*curr;

	curr = head;
	new = ft_calloc(1, sizeof(t_tmpfile));
	if (!new)
		return (NULL);
	new->name = get_tmp_name("aha");
	new->fd = -1;
	if (!head)
		head = new;
	else
	{
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
	return (head);
}