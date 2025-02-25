/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:24:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/25 20:27:47 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

#define CHUNK_SIZE 1024

typedef struct Chunk Chunk;

struct Chunk {
	Chunk		*next;
	size_t		count;
	size_t		capacity;
	uintptr_t	data[];
};

typedef struct {
	Chunk	*begin;
	Chunk	*end;
}	Arena;

Chunk	*new_chunk(size_t capacity);
void	free_chunk(Chunk *r);
void	*arena_alloc(Arena *a, size_t size_bytes);

#endif
