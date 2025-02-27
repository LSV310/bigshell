/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 12:09:30 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 17:06:38 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	init_history(t_history *history)
{
	history->size = 256;
	history->index = -1;
	history->history = ft_calloc(history->size, sizeof(char *));
	if (!history)
		return (0);
	return (1);
}

char	*history_up(t_history *history)
{
	if (history->index >= 0 && !history->history[history->index + 1])
		return (history->history[history->index]);
	history->index++;
	return (history->history[history->index]);
}

char	*history_down(t_history *history)
{
	if (history->index < 0)
		return (NULL);
	history->index--;
	if (history->index < 0)
		return (NULL);
	return (history->history[history->index]);
}

int	cmd_add_history(t_history *history, char *cmd)
{
	int	search_history;

	if (!history || !*cmd)
		return (1);
	search_history = ft_strstr_tab(history->history, cmd);
	if (search_history >= 0)
		return (shift_elem_up(history->history,
				history->history[search_history]), (history->index = -1), 1);
	history->index = 0;
	while (history->index + 5 < (int)history->size
		&& history->history[history->index] != 0)
		history->index++;
	if (history->index + 5 >= (int)history->size)
	{
		ft_realloc(history->history, history->size * 2, history->size);
		if (!history->history)
			return (0);
		while (history->history[history->index] != 0)
			history->index++;
	}
	history->history[history->index] = ft_strdup(cmd);
	shift_elem_up(history->history, history->history[history->index]);
	history->index = -1;
	return (1);
}
