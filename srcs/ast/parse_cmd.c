/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 14:22:43 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/05 18:18:22 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_cmd(t_list *tks)
{
	t_token	*tk;
	int		n;

	n = 1;
	while (tks && tks->content)
	{
		tk = tks->content;
		if (tk->type == ORT || tk->type == ANDT || tk->type == RPAR
			|| tk->type == ENDT)
			break ;
		if (tk->type == PIPE)
			n++;
	}
	return (n);
}

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
		return (0);
	else if (n > 1)
	{
		cmd->args = arena_calloc(arena, sizeof(char *) * (n));
		if (cmd->args == NULL)
			return (0);
		cmd->args[n] = NULL;
	}
	return (1);
}

int	is_cmd_token(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == NAME || tok->type == REDIN || tok->type == APPEN
		|| tok->type == HEREDOC || tok->type == REDOUT)
		return (1);
	else
		return (0);
}

int	in_out_token(t_token *tok, t_cmd *cmd)
{

	if (tok->type == REDIN)
		cmd->fdin = open(tok->str, O_RDONLY);
	else if (tok->type == REDOUT)
		cmd->fdout = open(tok->str, O_TRUNC | O_CREAT | O_WRONLY, 0644);
	else if (tok->type == HEREDOC)
		cmd->fdin = here_doc(tok->str);
	else if (tok->type == APPEN)
		cmd->fdout = open(tok->str, O_APPEND | O_CREAT | O_WRONLY, 0644);
	if (cmd->fdout == -1 || cmd->fdin == -1)
		return (0);
	return (1);
}

t_cmd	*parse_next_cmd(t_list **tks, t_arena *arena)
{
	t_cmd	*cmd;
	t_token	*tok;
	int		i;

	cmd = arena_calloc(arena, sizeof(cmd));
	if (!cmd_args_alloc(cmd, *tks, arena))
		return (NULL);
	i = 0;
	while (*tks && (**tks).content)
	{
		tok = (**tks).content;
		if (!is_cmd_token(tok) || !in_out_token(tok, cmd))
			break ;
		if (tok->type == NAME && cmd->cmd == NULL)
			cmd->cmd = tok->str;
		else if (tok->type == NAME && cmd->cmd != NULL)
			cmd->args[i++] = tok->str;
		*tks = (*tks)->next;
	}
	return ((t_cmd*)cmd);
}

t_cmd	**parse_pipeline(t_list **tks, t_arena *arena)
{
	t_cmd		**cmds;
	const int	n_cmd = count_cmd(*tks);
	int			i;

	cmds = arena_alloc((n_cmd + 1) * sizeof(t_cmd*), arena);
	if (!cmds)
		return (NULL);
	cmds[n_cmd] = NULL;
	i = 0;
	while (i < n_cmd)
	{
		cmds[i] = parse_next_cmd(tks, arena);
		if (!cmds[i])
			return (NULL);
		i++;
	}
	return (cmds);
}

t_ast	*init_cmd_node(t_list **tks, t_arena *arena)
{
	t_token	*token;
	t_ast	*ret;

	token = (**tks).content;
	if (token == NULL || token->type == ENDT || token->type == ORT ||
		token->type == ANDT || token->type == LPAR || token->type == RPAR)
		return (NULL);
	ret = arena_alloc(sizeof(t_ast), arena);
	if (!ret)
		return (NULL);
	ret->left = NULL;
	ret->right = NULL;
	return (ret);
}
