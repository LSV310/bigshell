/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:12:00 by agruet            #+#    #+#             */
/*   Updated: 2025/03/28 12:27:06 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	EOF_received(t_rline *line, t_readline *params)
{
	write(0, "\n", 1);
	clear_line(line, params->history, 1);
	params->quit_reason = RL_SUCCESS;
	return (0);
}

void	move_word(t_rline*line, int key)
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
