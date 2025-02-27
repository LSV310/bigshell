/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:30 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 14:07:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	init_history(t_history *history)
{
	history->size = 256;
	history->index = 0;
	history->history = ft_calloc(history->size, sizeof(char *));
	if (!history)
		return (0);
	return (1);
}

int	cmd_add_history(t_history *history, char *cmd)
{
	int	search_history;

	if (!history || !*cmd)
		return (1);
	search_history = ft_strstr_tab(history->history, cmd);
	if (search_history >= 0)
		return (shift_elem_up(history->history,
				history->history[search_history]), 1);
	while (history->index < history->size - 5
		&& history->history[history->index] != 0)
		history->index++;
	if (history->index >= history->size - 5)
	{
		ft_realloc(history->history, history->size * 2, history->size);
		if (!history->history)
			return (0);
		while (history->history[history->index] != 0)
			history->index++;
	}
	history->history[history->index] = ft_strdup(cmd);
	shift_elem_up(history->history, history->history[history->index]);
	return (1);
}
