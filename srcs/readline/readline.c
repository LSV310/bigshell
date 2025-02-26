/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:21:42 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 18:24:45 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_reading(t_mini *minishell)
{
	int		key;
	char	*current_line;
	int		size_allocated;
	int		cursor_pos;

	(void)minishell;
	cursor_pos = 0;
	size_allocated = 1024;
	current_line = malloc(sizeof(char) * size_allocated);
	if (!current_line)
		return (0);
	ft_fprintf(0, "minishell$> ");
	set_raw_mode();
	while (1)
	{
		key = read_key();
		if (key == 4 && cursor_pos == 0)
			break ;
		if (ft_isprint(key) && key != 10)
		{
			write(STDOUT_FILENO, &key, 1);
			current_line[cursor_pos] = key;
			cursor_pos++;
		}
		else if (key == '\n' || key == -1)
		{
			cursor_pos = 0;
			write(0, "\n", 1);
			ft_fprintf(0, "minishell$> ");
			if (key == '\n')
				(void)current_line;
			free(current_line);
			size_allocated = 1024;
			current_line = malloc(sizeof(char) * size_allocated);
			if (!current_line)
				return (reset_terminal_mode(), 0);
		}
		if (cursor_pos + 1 >= size_allocated)
		{
			current_line = ft_realloc(current_line, size_allocated * 2, size_allocated);
			if (!current_line)
				return (reset_terminal_mode(), 0);
			size_allocated *= 2;
		}
	}
	free(current_line);
	write(0, "\n", 1);
	reset_terminal_mode();
	return (1);
}
