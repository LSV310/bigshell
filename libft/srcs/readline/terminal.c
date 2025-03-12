/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:13:55 by agruet            #+#    #+#             */
/*   Updated: 2025/03/10 16:55:00 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	set_raw_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

void	reset_terminal_mode(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int	find_sequence(char *seq)
{
	if (seq[1] == 'A')
		return (-12);
	else if (seq[1] == 'B')
		return (-13);
	else if (seq[1] == 'C')
		return (-14);
	else if (seq[1] == 'D')
		return (-15);
	else if (seq[1] == 'H')
		return (-16);
	else if (seq[1] == 'F')
		return (-17);
	else if (seq[1] == '3')
	{
		read(STDIN_FILENO, &seq[1], 1);
		return (-18);
	}
	else if (seq[1] == '1')
		read(STDIN_FILENO, &seq[1], 3);
	return (0);
}

int	read_key(void)
{
	char	ch;
	char	seq[3];

	if (read(STDIN_FILENO, &ch, 1) != 1)
		return (-1);
	if (ch == 27)
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1
			|| read(STDIN_FILENO, &seq[1], 1) != 1)
			return (-1);
		if (seq[0] == '[')
			return (find_sequence(seq));
	}
	return (ch);
}

int	reset_line(t_readline *line, char *prompt)
{
	char	*cpy;

	ft_fprintf(0, "\r%s", prompt);
	cpy = ft_strdup(line->current_line);
	if (!cpy)
		return (0);
	ft_memset(cpy, ' ', line->cursor);
	write(STDIN_FILENO, cpy, line->cursor);
	ft_memset(cpy, '\b', line->cursor);
	write(STDIN_FILENO, cpy, line->cursor);
	free(cpy);
	return (1);
}
