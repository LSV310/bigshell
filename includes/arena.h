/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:24:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/05 14:55:04 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

# define CHUNK_SIZE 1024

typedef struct s_chunk	t_chunk;

struct s_chunk {
	t_chunk		*next;
	size_t		count;
	size_t		capacity;
	uintptr_t	data[];
};

typedef struct s_arena{
	t_chunk	*begin;
	t_chunk	*end;
	int		freed;
}	t_arena;

t_chunk	*region_create(size_t capacity);
t_arena	*arena_init(void);
void	*arena_free(t_arena *arena);
void	*arena_alloc(size_t size, t_arena *arena);
t_list	*ar_lstnew(void *content, t_arena *arena);
void	*arena_calloc(t_arena *arena, size_t size);
char	*ar_strndup(const char *s, size_t n, t_arena *arena);

#endif
