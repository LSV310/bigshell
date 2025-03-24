/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 05:12:16 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 16:41:16 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	stdin_to_pipe(int to_write, char *delimiter, bool expand, t_shell *shell)
{
	char	*line;
	t_dlist	*history;

	history = NULL;
	line = ft_readline("> ", &history, false);
	if (expand)
		line = env_exp(line, shell);
	while (line && ft_strcmp(line, delimiter) != 0)
	{
		write(to_write, line, ft_strlen(line));
		write(to_write, "\n", 1);
		free(line);
		line = ft_readline("> ", &history, false);
		if (expand)
			line = env_exp(line, shell);
	}
	if (!line)
	{
		ft_fprintf(2, "warning: here-document delimited by end-of-file");
		ft_fprintf(2, "(wanted `%s')\n", delimiter);
	}
	else
		free(line);
	ft_dlstclear(&history, &free_content);
}

int	here_doc(char *delimiter, bool expand, t_shell *shell)
{
	t_pipe	fds;

	fds.read_fd = -1;
	if (pipe((int *) &fds) == -1)
		perror("");
	else
	{
		stdin_to_pipe(fds.write_fd, delimiter, expand, shell);
		close(fds.write_fd);
	}
	return (fds.read_fd);
}

void	delimiter_parse(t_token	*tok, char *dest, bool *exp_mode)
{
	int	i;

	i = 0;
	while (i < tok->len)
	{
		if (char_in_set(tok->p[i], "\"\'"))
		{
			*exp_mode = false;
			continue;
		}
		*dest = tok->p[i];
		i++;
		dest += 1;
	}
}

bool	token_heredoc(t_token *tok, t_shell *shell)
{
	char	*del;
	bool	do_exp;

	del = arena_calloc(shell->arena, tok->len);
	if (!del)
		return (false);
	delimiter_parse(tok, del, &do_exp);
	tok->str = itoarena(here_doc(del, do_exp, shell), shell->arena);
	return (true);
}
