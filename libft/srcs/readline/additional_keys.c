/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_keys.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:45:38 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 17:52:42 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	up_arrow(t_readline *line, t_history *history, char *prompt)
{
	char	*next;
	int		len;

	next = history_up(history);
	if (!next)
		return (1);
	ft_fprintf(0, "\r%s", prompt);
	ft_memset(line->current_line, ' ', line->cursor);
	write(STDIN_FILENO, line->current_line, line->cursor);
	ft_memset(line->current_line, '\b', line->cursor);
	write(STDIN_FILENO, line->current_line, line->cursor);
	free(line->current_line);
	line->current_line = calloc(ft_strlen(next) + 100, sizeof(char));
	if (!line->current_line)
		return (0);
	len = ft_strlen(next);
	ft_strlcpy(line->current_line, next, len);
	line->cursor = len;
	line->size = len + 100;
	ft_fprintf(0, next);
	return (1);
}

int	down_arrow(t_readline *line, t_history *history, char *prompt)
{
	char	*prev;
	int		len;

	ft_fprintf(0, "\r%s", prompt);
	ft_memset(line->current_line, ' ', line->cursor);
	write(STDIN_FILENO, line->current_line, line->cursor);
	ft_memset(line->current_line, '\b', line->cursor);
	write(STDIN_FILENO, line->current_line, line->cursor);
	ft_memset(line->current_line, '\0', line->cursor);
	line->cursor = 0;
	prev = history_down(history);
	if (!prev)
		return (1);
	free(line->current_line);
	len = ft_strlen(prev);
	line->current_line = calloc(len + 100, sizeof(char));
	if (!line->current_line)
		return (0);
	ft_strlcpy(line->current_line, prev, len);
	line->cursor = len;
	line->size = len + 100;
	ft_fprintf(0, prev);
	return (1);
}
