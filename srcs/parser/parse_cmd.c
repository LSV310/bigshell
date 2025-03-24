/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:06:31 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 00:20:34 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_name(t_list *tks)
{
	t_token	*tk;
	int		n;

	n = 0;
	while (tks && tks->content)
	{
		tk = tks->content;
		if (tk->type == ORT || tk->type == ANDT || tk->type == RPAR
			|| tk->type == ENDT || tk->type == PIPE)
			break ;
		if (tk->type == NAME)
			n++;
		tks = tks->next;
	}
	return (n);
}

int	cmd_args_alloc(t_cmd *cmd, t_list *tks, t_arena *arena)
{
	int	n;

	if (!cmd)
		return (0);
	n = count_name(tks);
	if (n == 0)
		return (1);
	else
	{
		cmd->args = arena_calloc(arena, sizeof(char *) * (n + 1));
		if (cmd->args == NULL)
			return (0);
		cmd->args[0] = "test";
		cmd->args[n] = NULL;
	}
	cmd->fdin = STDIN_FILENO;
	cmd->fdout = STDOUT_FILENO;
	return (1);
}

void	replace_fd(int fd, t_cmd *cmd, bool is_in)
{
	if (is_in)
	{
		cmd->fdin = fd;
		if (fd >= 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
	else
	{
		cmd->fdout = fd;
		if (fd >= 0)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
	}
}

int	in_out_token(t_token *tok, t_cmd *cmd)
{
	if (tok->type == REDIN)
		replace_fd(open(tok->str, O_RDONLY), cmd, true);
	else if (tok->type == REDOUT)
		replace_fd(open(tok->str, O_TRUNC | O_CREAT | O_WRONLY, 0666), cmd, false);
	else if (tok->type == HEREDOC)
		replace_fd(atoi(tok->str), cmd, true);
	else if (tok->type == APPEN)
		replace_fd(open(tok->str, O_APPEND | O_CREAT | O_WRONLY, 0666), cmd, false);
	if (cmd->fdout == -1 || cmd->fdin == -1)
		return (0);
	return (1);
}

t_cmd	*parse_cmd(t_list *tks, t_arena *arena)
{
	t_cmd	*cmd;
	t_token	*tok;
	int		i;
	t_list	*cur;

	if (!tks)
		return (NULL);
	cur = tks;
	cmd = arena_calloc(arena, sizeof(t_cmd));
	if (!cmd_args_alloc(cmd, cur, arena))
		return (NULL);
	i = 0;
	while (cur && cur->content)
	{
		tok = cur->content;
		if (!is_cmd_token(tok) || !in_out_token(tok, cmd))
			break ;
		if (tok->type == NAME && cmd->name == NULL)
			cmd->name = tok->str;
		if (tok->type == NAME)
			cmd->args[i++] = tok->str;
		cur = cur->next;
	}
	return (cmd);
}
