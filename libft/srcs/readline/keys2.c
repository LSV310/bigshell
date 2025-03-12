/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:44:33 by agruet            #+#    #+#             */
/*   Updated: 2025/03/10 12:38:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*new_line(t_readline *line, char *hist)
{
	int		len;

	len = ft_strlen(hist);
	line->current_line = ft_calloc(len + 100, sizeof(char));
	if (!line->current_line)
		return (NULL);
	ft_strlcpy(line->current_line, hist, len + 1);
	line->cursor = len;
	line->end = len;
	line->size = len + 100;
	ft_fprintf(0, hist);
	return (line->current_line);
}

int	up_arrow(t_readline *line, t_dlist **history, char *prompt)
{
	char	*next;

	next = history_up(history);
	if (!next)
		return (1);
	if (!reset_line(line, prompt))
		return (0);
	if ((*history)->prev == ft_dlstfirst(*history))
	{
		if ((*history)->prev->content != line->current_line)
			free((*history)->prev->content);
		(*history)->prev->content = ft_strdup(line->current_line);
		if (!(*history)->prev->content)
			return (0);
	}
	free(line->current_line);
	if (!new_line(line, next))
		return (0);
	return (1);
}

int	down_arrow(t_readline *line, t_dlist **history, char *prompt)
{
	char	*prev;

	prev = history_down(history);
	if (!prev)
		return (1);
	if (!reset_line(line, prompt))
		return (0);
	free(line->current_line);
	if (!new_line(line, prev))
		return (0);
	return (1);
}

void	home_key(t_readline *line)
{
	while (line->cursor > 0)
	{
		line->cursor--;
		ft_fprintf(0, "\b");
	}
}

void	end_key(t_readline *line)
{
	while (line->cursor < line->end)
	{
		ft_fprintf(0, "%c", line->current_line[line->cursor]);
		line->cursor++;
	}
}
