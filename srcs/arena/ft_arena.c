/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arena.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:01:47 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/26 15:38:13 by tgallet          ###   ########.fr       */
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
