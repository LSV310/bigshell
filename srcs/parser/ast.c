/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:41:03 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/20 01:28:29 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	log_cur_token(t_list **tokens)
{
	t_token	*tok;

	tok = (*tokens)->content;
	printf("current token: %s (%s)\n", tok->str, toktype_to_string(tok->type));
}

t_ast	*createNode(t_node_type type, t_list **tokens, t_arena *arena, t_ast *childs[2])
{
	t_list	**commands;
	t_ast	*node;

	if (tokens)
	{
		commands = ptr_arr_pipeline(*tokens, arena);
		skip_pipeline(tokens);
	}
	else
		commands = NULL;
	node = arena_alloc(sizeof(t_ast), arena);
	if (!node)
		return (NULL);
	node->type = type;
	node->cmds = commands;
	node->left = childs[0];
	node->right = childs[1];
	return (node);
}

// Moves to the next token by incrementing 'pos'
static bool advance_token(t_list **tokens)
{
	t_token	*tok;

	tok = (*tokens)->content;
	// printCurToken(tokens);
	ft_printf("advancing token: %s ", toktype_to_string(tok->type));
	*tokens = (*tokens)->next;
	tok = (*tokens)->content;
	ft_printf("to %s\n", toktype_to_string(tok->type));
	if (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type == ENDT)
			return (false);
		else
			return (true);
	}
	else
		return (false);
}

t_ast	*parse_expr(t_list **tokens, t_arena *arena);

t_ast	*parse_par(t_list **tokens, t_arena *arena)
{
	t_ast	*ret;
	t_token	*tok;

	if (!advance_token(tokens))
		return (NULL);
	ret = parse_expr(tokens, arena);
	tok = (**tokens).content;
	if (tok->type != RPAR)
		return (NULL);
	advance_token(tokens);
	return (ret);
}

t_ast	*parse_logic(t_list **tokens, t_arena *arena, t_ast *left, t_token_type type)
{
	t_ast	*right;
	t_token	*tok;

	log_cur_token(tokens);
	if (!advance_token(tokens))
		return (NULL);
	right = parse_expr(tokens, arena);
	if (!right)
		return (NULL);
	if (type == ORT)
		return (createNode(ND_OR, NULL, arena, (t_ast *[]){left, right}));
	else if (type == ANDT)
		return (createNode(ND_AND, NULL, arena, (t_ast *[]){left, right}));
	else
		return (NULL);
}

t_ast	*parse_expr(t_list **tokens, t_arena *arena)
{
	t_ast	*left;
	t_token	*tok;

	tok = (**tokens).content;
	if (tok->type == LPAR)
		left = parse_par(tokens, arena);
	else if (is_cmd_token(tok))
		left = createNode(ND_CMD, tokens, arena, (t_ast *[]){NULL, NULL});
	else
		return (NULL);
	// printCurToken(tokens);
	if (!left)
		return (NULL);
	tok = (**tokens).content;
	if (tok->type == ENDT || tok->type == RPAR)
		return (left);
	else if (tok->type == ORT || tok->type == ANDT)
		return (parse_logic(tokens, arena, left, tok->type));
}

// GRAMMAR
// terminal things are: OR AND CMD L_PAR R_PAR ENDT
// expr		:= CMD | logic | par
// logic	:= expr AND expr | expr OR expr
// pars		:= L_PAR expr R_PAR

// cmd1 || (cmd2 && cmd3)
// (cmd1 && cmd2 || cmd3) || cmd4
// cmd2 && cmd3
t_ast *build_ast(t_list *tks, t_arena *arena)
{
	t_ast	*root;
	t_token	*tok;

	root = parse_expr(&tks, arena);
	if (!tks || !tks->content)
	{
		ft_printf("null lst error\n");
		if (!root)
			ft_putstr_fd("bad input caused a parsing error !\n", STDERR_FILENO);
		return (root);
	}
	tok = tks->content;
	if (!root)
		ft_putstr_fd("bad input caused a parsing error !\n", STDERR_FILENO);
	if (tok->type != ENDT)
		ft_printf("last token was (%s) unstead of (ENDT)\n", toktype_to_string(tok->type));
	return (root);
}
