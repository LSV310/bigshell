/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:44:33 by agruet            #+#    #+#             */
/*   Updated: 2025/03/03 15:49:30 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	up_arrow(t_readline *line, t_dlist **history, char *prompt)
{
	char	*next;
	int		len;

	next = history_up(history);
	if (!next)
		return (1);
	if (!reset_line(line, prompt))
		return (0);
	if ((*history)->prev->content == line->current_line)
	{
		(*history)->prev->content = ft_strdup(line->current_line);
		if (!(*history)->prev->content)
			return (0);
	}
	free(line->current_line);
	len = ft_strlen(next);
	line->current_line = ft_calloc(len + 100, sizeof(char));
	if (!line->current_line)
		return (0);
	ft_strlcpy(line->current_line, next, len + 1);
	line->cursor = len;
	line->end = len;
	line->size = len + 100;
	ft_fprintf(0, next);
	return (1);
}

int	down_arrow(t_readline *line, t_dlist **history, char *prompt)
{
	char	*prev;
	int		len;

	prev = history_down(history);
	if (!prev)
		return (1);
	if (!reset_line(line, prompt))
		return (0);
	free(line->current_line);
	len = ft_strlen(prev);
	line->current_line = ft_calloc(len + 100, sizeof(char));
	if (!line->current_line)
		return (0);
	ft_strlcpy(line->current_line, prev, len + 1);
	line->cursor = len;
	line->end = len;
	line->size = len + 100;
	ft_fprintf(0, prev);
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

void	del_key(t_readline *line)
{
	if (line->cursor == line->end)
		return ;
	ft_fprintf(0, "%c", line->current_line[line->cursor++]);
	back_space(line);
}
