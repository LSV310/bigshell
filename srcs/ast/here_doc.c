/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 05:12:16 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/18 13:06:06 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stdin_to_pipe(int to_write, char *delimiter)
{
	char	*line;
	t_dlist	*history;

	history = NULL;
	line = ft_readline("> ", &history, false);
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		write(to_write, line, ft_strlen(line));
		free(line);
		line = ft_readline("> ", &history, false);
	}
	if (!line)
	{
		ft_fprintf(2, "warning: here-document delimited by end-of-file ");
		ft_fprintf(2, "(wanted `%s')\n", delimiter);
	}
	else
		free(line);
	ft_dlstclear(&history, &free_content);
}
// TODO: implement env var expansion
int	here_doc(char *delimiter)
{
	t_pipe	fds;

	if (pipe((int *) &fds) == -1)
		perror("pipe failed");
	else
	{
		stdin_to_pipe(fds.write_fd, delimiter);
		close(fds.write_fd);
	}
	return (fds.read_fd);
}

/* int	main(void)
{
	here_doc("eof");
} */
