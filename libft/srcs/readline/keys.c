/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:45:38 by agruet            #+#    #+#             */
/*   Updated: 2025/03/07 11:49:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	printkey(int key, t_readline *line)
{
	size_t	len;

	if (key == '\n')
		return (1);
	write(STDIN_FILENO, &key, 1);
	len = ft_strlen(line->current_line + line->cursor);
	if (len > 0)
	{
		ft_memmove(line->current_line + line->cursor + 1,
			line->current_line + line->cursor, len);
		ft_fprintf(0, "%s", line->current_line + line->cursor + 1);
		while (len-- > 0)
			write(STDIN_FILENO, "\b", 1);
	}
	line->current_line[line->cursor++] = key;
	line->end++;
	return (0);
}

static void	move_key(t_readline *line, int key)
{
	if (key == -14 && line->cursor < line->end)
	{
		ft_fprintf(0, "%c", line->current_line[line->cursor]);
		line->cursor++;
	}
	else if (key == -15 && line->cursor > 0)
	{
		line->cursor--;
		ft_fprintf(0, "\b");
	}
}

void	back_space(t_readline *line)
{
	size_t	len;
	size_t	i;

	if (line->cursor <= 0)
		return ;
	i = 0;
	len = ft_strlen(line->current_line + line->cursor) + 1;
	while (i++ < len)
		write(STDIN_FILENO, " ", 1);
	i = 0;
	while (i++ < len)
		write(STDIN_FILENO, "\b", 1);
	line->cursor--;
	line->end--;
	ft_fprintf(0, "\b \b");
	if (len > 1)
	{
		ft_memmove(line->current_line + line->cursor,
			line->current_line + line->cursor + 1, len);
		ft_fprintf(0, "%s", line->current_line + line->cursor);
		i = 0;
		while (++i < len)
			write(STDIN_FILENO, "\b", 1);
	}
	line->current_line[line->end] = '\0';
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
		back_space(line);
	else if (history && key == -12 && !up_arrow(line, history, prompt))
		return (0);
	else if (history && key == -13 && !down_arrow(line, history, prompt))
		return (0);
	else if (key == -14 || key == -15)
		move_key(line, key);
	else if (key == -16)
		home_key(line);
	else if (key == -17)
		end_key(line);
	else if (key == -18)
		del_key(line);
	return (1);
}
