/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremove_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:59:15 by agruet            #+#    #+#             */
/*   Updated: 2025/02/28 11:10:24 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	lst_remove_node(t_list **lst, t_list *node, void (*del)(void*))
{
	t_list	*current;
	t_list	*previous;

	if (!lst || !*lst || !node)
		return ;
	current = *lst;
	previous = *lst;
	while (current)
	{
		if (current == node)
		{
			if (current == previous)
				*lst = node->next;
			else
				previous->next = node->next;
			ft_lstdelone(node, del);
			return ;
		}
		previous = current;
		current = current->next;
	}
}
