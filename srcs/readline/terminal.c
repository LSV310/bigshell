/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:13:55 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 17:28:22 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to set the terminal to raw mode
void set_raw_mode(void)
{
	struct termios	term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

// Function to restore the terminal to normal mode
void reset_terminal_mode(void)
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= (ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);
}

int read_key(void)
{
	char	ch;
	char	seq[3];

	if (read(STDIN_FILENO, &ch, 1) != 1)
		return (-1);
	if (ch == 27)
	{
		if (read(STDIN_FILENO, &seq[0], 1) != 1 || read(STDIN_FILENO, &seq[1], 1) != 1)
			return (-1);
		if (seq[0] == '[')
		{
			if (seq[1] == 'A')
				return (-12);
			else if (seq[1] == 'B')
				return (-13);
		}
	}
	return (ch);
}
