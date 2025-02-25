/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:27:24 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/25 20:28:12 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

Chunk *region_create(size_t capacity)
{
	Chunk	*region;

	region = (Chunk *) malloc(sizeof(Chunk) + capacity * sizeof(uintptr_t));
	if (region == NULL)
		return NULL;
	region->next = NULL;
	region->count = 0;
	region->capacity = capacity;
	return (region);
}

void	arena_init(Arena *arena)
{
	arena->begin = region_create(CHUNK_SIZE);
	arena->end = arena->begin;
}

void	arena_free(Arena *arena)
{
	Chunk *region;
	Chunk *next;

	region = arena->begin;
	while (region != NULL) {
		next = region->next;
		free(region);
		region = next;
	}
	arena->begin = NULL;
	arena->end = NULL;
}

void *arena_alloc(Arena *arena, size_t size)
{
	size_t	capacity;
	Chunk	*new_chunk;
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
			return (NULL);
		arena->end->next = new_chunk;
		arena->end = new_chunk;
	}
	res = (void *)(arena->end->data + arena->end->count);
	arena->end->count += size;
	return (res);
}
