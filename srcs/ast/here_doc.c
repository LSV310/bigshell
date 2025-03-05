/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 05:12:16 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/05 17:16:09 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stdin_to_pipe(int to_write, char *delimiter)
{
	char	*line;

	write(1, "heredoc>", 9);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		write(to_write, line, ft_strlen(line));
		free(line);
		write(1, "heredoc> ", 10);
		line = get_next_line(STDIN_FILENO);
	}
	free(line);
}

int	here_doc(char *delimiter)
{
	t_pipe	fds;

	if (pipe((int *) &fds) == -1)
	{
		perror("pipe failed");
	}
	else
	{
		delimiter = ft_strjoin(delimiter, "\n");
		stdin_to_pipe(fds.write_fd, delimiter);
		free(delimiter);
		close(fds.write_fd);
	}
	return (fds.read_fd);
}
/*
int main(void)
{
	here_doc("eof");
}
*/
