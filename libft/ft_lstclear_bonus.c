/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ketrevis <ketrevis@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 09:44:38 by ketrevis          #+#    #+#             */
/*   Updated: 2023/10/31 16:13:40 by ketrevis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*lst_tmp;

	while (*lst != NULL)
	{
		lst_tmp = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = lst_tmp;
	}
}
