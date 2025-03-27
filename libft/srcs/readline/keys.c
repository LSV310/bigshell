/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 15:45:38 by agruet            #+#    #+#             */
/*   Updated: 2025/03/27 11:14:04 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printkey(int key, t_readline *line)
{
	size_t	len;
	char	*temp;

	if (key == '\n')
		return (1);
	if ((key == '\t' || key == '\f') && isatty(STDIN_FILENO))
		return (0);
	write(STDIN_FILENO, &key, 1);
	len = ft_strlen(line->current_line + line->cursor);
	if (len > 0)
	{
		ft_memmove(line->current_line + line->cursor + 1,
			line->current_line + line->cursor, len);
		ft_fprintf(0, "%s", line->current_line + line->cursor + 1);
		temp = ft_strdup(line->current_line);
		write_x_times(temp, '\b', len);
		free(temp);
	}
	line->current_line[line->cursor++] = key;
	line->end++;
	return (0);
}

static void	move_key(t_readline *line, int key)
{
	if (key == RARROW && line->cursor < line->end)
	{
		ft_fprintf(0, "%c", line->current_line[line->cursor]);
		line->cursor++;
	}
	else if (key == LARROW && line->cursor > 0)
	{
		line->cursor--;
		ft_fprintf(0, "\b");
	}
}

void	back_space(t_readline *line)
{
	size_t	len;
	char	*temp;

	if (line->cursor <= 0)
		return ;
	len = ft_strlen(line->current_line + line->cursor) + 1;
	temp = ft_strdup(line->current_line);
	write_x_times(temp, ' ', len);
	write_x_times(temp, '\b', len);
	line->cursor--;
	line->end--;
	write(0, "\b \b", 3);
	if (len > 1)
	{
		ft_memmove(line->current_line + line->cursor,
			line->current_line + line->cursor + 1, len);
		ft_fprintf(0, "%s", line->current_line + line->cursor);
		write_x_times(temp, '\b', len - 1);
	}
	free(temp);
	line->current_line[line->end] = '\0';
}

void	del_key(t_readline *line)
{
	if (line->cursor == line->end)
		return ;
	ft_fprintf(0, "%c", line->current_line[line->cursor++]);
	back_space(line);
}

int	other_key(int key, t_readline *line, char *prompt, t_dlist **history)
{
	if (key == EOF_K && line->end == 0)
	{
		write(0, "\n", 1);
		ft_printf("exit\n");
		clear_line(line, history, 1);
		return (0);
	}
	else if (key == READ_FAILED && !rl_signal_received(line, history, prompt))
		return (0);
	else if (key == DEL_K)
		back_space(line);
	else if (history && key == UARROW && !up_arrow(line, history))
		return (0);
	else if (history && key == DARROW && !down_arrow(line, history))
		return (0);
	else if (key == RARROW || key == LARROW)
		move_key(line, key);
	else if (key == HOME)
		home_key(line);
	else if (key == END)
		end_key(line);
	else if (key == DEL || key == EOF_K)
		del_key(line);
	return (1);
}
