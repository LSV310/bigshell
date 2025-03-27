/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:12:00 by agruet            #+#    #+#             */
/*   Updated: 2025/03/27 15:56:42 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	move_word(t_readline *line, int key)
{
	if (key == CL_ARROW)
	{
		while (line->cursor > 0 && line->current_line[line->cursor - 1] == ' ')
			move_key(line, LARROW);
		while (line->cursor > 0 && line->current_line[line->cursor - 1] != ' ')
			move_key(line, LARROW);
		return ;
	}
	while (line->cursor < line->end && line->current_line[line->cursor] == ' ')
		move_key(line, RARROW);
	while (line->cursor < line->end && line->current_line[line->cursor] != ' ')
		move_key(line, RARROW);
	}
