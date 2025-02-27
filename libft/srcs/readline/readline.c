/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:21:42 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 12:59:44 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	new_buffer(t_readline *line)
{
	line->cursor = 0;
	line->size = 1024;
	line->current_line = ft_calloc(line->size, sizeof(char));
	if (!line->current_line)
		return (0);
	return(1);
}

static int	signal_received(t_readline *line, char *prompt)
{
	free(line->current_line);
	if (!new_buffer(line))
		return (0);
	ft_fprintf(0, "\n%s", prompt);
	return (1);
}

static int	line_too_long(t_readline *line)
{
	if (line->cursor + 1 >= line->size)
	{
		line->current_line = ft_realloc(line->current_line,
			line->size * 2, line->size);
		if (!line->current_line)
			return (0);
		line->size *= 2;
	}
	return (1);
}

static int	other_key(int key, t_readline *line, char *prompt)
{
	if (key == 4 && line->cursor == 0)
	{
		free(line->current_line);
		return (write(0, "\n", 1), 0);
	}
	else if (key == -1 && !signal_received(line, prompt))
		return (0);
	return (1);
}

char	*read_line(char *prompt, t_history *history)
{
	int			key;
	t_readline	line;

	ft_fprintf(0, prompt);
	if (!new_buffer(&line))
		return (NULL);
	set_raw_mode();
	while (1)
	{
		key = read_key();
		if (ft_isprint(key))
		{
			if (key == '\n')
				break ;
			write(STDOUT_FILENO, &key, 1);
			line.current_line[line.cursor++] = key;
		}
		else if (!other_key(key, &line, prompt))
			return (reset_terminal_mode(), NULL);
		if (!line_too_long(&line))
			return (reset_terminal_mode(), NULL);
	}
	if (!cmd_add_history(history, line.current_line))
		return (reset_terminal_mode(), NULL);
	return (write(0, "\n", 1), reset_terminal_mode(), line.current_line);
}
