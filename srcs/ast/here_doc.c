/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 05:12:16 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/03 16:28:26 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_heredocs(t_list *tks)
{
	t_token	*token;

	while (tks && tks->content)
	{
		token = tks->content;
		if (token->type == HEREDOC)
			close(ft_atoi(token->str));
		tks = tks->next;
	}
}

void	stdin_to_pipe(int to_write, char *delim, bool expand, t_shell *shell)
{
	char		*line;
	t_dlist		*history;
	t_readline	rl_params;

	history = NULL;
	init_readline_params(&rl_params);
	rl_params.history = &history;
	rl_params.prompt = "> ";
	line = ft_readline(&rl_params);
	while (line && ft_strcmp(line, delim) != 0)
	{
		if (expand)
			line = env_exp(line, shell);
		write(to_write, line, ft_strlen(line));
		write(to_write, "\n", 1);
		free(line);
		line = ft_readline(&rl_params);
	}
	if (!line && rl_params.quit_reason == RL_FINISHED)
		ft_fprintf(2, "warning: here-document delimited by end-of-file \
			(wanted '%s')\n", delim);
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
	size_t	i;

	i = 0;
	*exp_mode = true;
	while (i < tok->len)
	{
		if (char_in_set(tok->p[i], "\"\'"))
		{
			*exp_mode = false;
			i++;
			continue ;
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

	del = arena_calloc(shell->arena, tok->len + 1);
	if (!del)
		return (false);
	delimiter_parse(tok, del, &do_exp);
	tok->str = itoarena(here_doc(del, do_exp, shell), shell->arena);
	return (true);
}
