/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:27:24 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/27 14:08:54 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/arena.h"

t_chunk	*region_create(size_t capacity)
{
	t_chunk	*region;

	region = (t_chunk *) malloc(sizeof(t_chunk) + capacity * sizeof(uintptr_t));
	if (region == NULL)
		return (NULL);
	region->next = NULL;
	region->count = 0;
	region->capacity = capacity;
	return (region);
}

t_arena	*arena_init(void)
{
	t_arena	*arena;

	arena = malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->begin = region_create(CHUNK_SIZE);
	arena->end = arena->begin;
	return (arena);
}

void	*arena_free(t_arena *arena)
{
	t_chunk	*region;
	t_chunk	*next;

	region = arena->begin;
	while (region != NULL)
	{
		next = region->next;
		free(region);
		region = next;
	}
	arena->begin = NULL;
	arena->end = NULL;
	free(arena);
	return (NULL);
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	size_t	capacity;
	t_chunk	*new_chunk;
	void	*res;

	if (!arena || !arena->end || !arena->begin)
		return (NULL);
	size = (size + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);
	if (arena->end->count + size > arena->end->capacity)
	{
		capacity = CHUNK_SIZE;
		if (capacity < size)
			capacity = size;
		new_chunk = region_create(capacity);
		if (new_chunk == NULL)
			return (arena_free(arena));
		arena->end->next = new_chunk;
		arena->end = new_chunk;
	}
	res = (void *)(arena->end->data + arena->end->count);
	arena->end->count += size;
	return (res);
}

void	*arena_calloc(t_arena *arena, size_t size)
{
	void	*res;

	res = arena_alloc(arena, size);
	if (!res)
		return (NULL);
	ft_memset(res, 0, size);
	return (res);
}
