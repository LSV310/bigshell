/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:01:47 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/17 11:52:35 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*ar_lstnew(void *content, t_arena *arena)
{
	t_list	*new;

	new = arena_alloc(sizeof(t_list), arena);
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

char	*ar_strndup(const char *s, size_t n, t_arena *arena)
{
	char	*new;
	size_t	i;

	i = 0;
	new = arena_alloc(sizeof(char) * (n + 1), arena);
	if (!new)
		return (NULL);
	while (s && s[i] && i < n)
	{
		new[i] = s[i];
		i++;
	}
	new[n] = 0;
	return (new);
}

t_list	*arlst_remove_node(t_list **lst, t_list *node)
{
	t_list	*current;
	t_list	*previous;

	if (!lst || !*lst || !node)
		return (NULL);
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
			return (node->next);
		}
		previous = current;
		current = current->next;
	}
	return (NULL);
}
