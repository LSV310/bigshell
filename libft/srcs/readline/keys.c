/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:45:38 by agruet            #+#    #+#             */
/*   Updated: 2025/03/03 11:31:31 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	printkey(int key, t_readline *line)
{
	if (key == '\n')
		return (1);
	write(STDOUT_FILENO, &key, 1);
	line->current_line[line->cursor++] = key;
	return (0);
}

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
		if (!(*history)->content)
			return (0);
	}
	free(line->current_line);
	len = ft_strlen(next);
	line->current_line = ft_calloc(len + 100, sizeof(char));
	if (!line->current_line)
		return (0);
	ft_strlcpy(line->current_line, next, len + 1);
	line->cursor = len;
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
	line->size = len + 100;
	ft_fprintf(0, prev);
	return (1);
}

int	other_key(int key, t_readline *line, char *prompt, t_dlist **history)
{
	if (key == 4 && line->cursor == 0)
	{
		clear_line(line, history, 1);
		return (write(0, "\n", 1), 0);
	}
	else if (key == -1 && !signal_received(line, history, prompt))
		return (0);
	else if (key == 127)
	{
		if (line->cursor > 0)
		{
			line->cursor--;
			line->current_line[line->cursor] = '\0';
			ft_fprintf(0, "\b \b");
		}
	}
	else if (history && key == -12 && !up_arrow(line, history, prompt))
		return (0);
	else if (history && key == -13 && !down_arrow(line, history, prompt))
		return (0);
	return (1);
}
