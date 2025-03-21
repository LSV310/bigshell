/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:01:47 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/21 13:05:44 by tgallet          ###   ########.fr       */
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
	return (*lst);
}

void	reset_arena(t_arena **arena)
{
	arena_regions_free(*arena);
	free (*arena);
	*arena = arena_init();
}


