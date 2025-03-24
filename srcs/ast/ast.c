/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:41:03 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 21:08:12 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_node(t_node_type type,
	t_list **tokens, t_arena *arena, t_ast *childs[2])
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

t_ast	*parse_logic(t_list **tokens, t_arena *arena,
	t_ast *left, t_token_type type)
{
	t_ast	*right;
	t_token	*tok;

	if (!advance_token(tokens))
		return (NULL);
	right = parse_expr(tokens, arena);
	if (!right)
		return (NULL);
	if (type == ORT)
		return (create_node(ND_OR, NULL, arena, (t_ast *[]){left, right}));
	else if (type == ANDT)
		return (create_node(ND_AND, NULL, arena, (t_ast *[]){left, right}));
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
		left = create_node(ND_CMD, tokens, arena, (t_ast *[]){NULL, NULL});
	else
		return (create_node(ND_NULL, NULL, arena, (t_ast *[]){NULL, NULL}));
	if (!left)
		return (NULL);
	tok = (**tokens).content;
	if (tok->type == ENDT || tok->type == RPAR)
		return (left);
	else if (tok->type == ORT || tok->type == ANDT)
		return (parse_logic(tokens, arena, left, tok->type));
	return (left);
}

t_ast	*build_ast(t_list *tks, t_shell *shell)
{
	t_ast	*root;
	t_token	*tok;

	root = parse_expr(&tks, shell->arena);
	if (!tks || !tks->content)
	{
		ft_fprintf(2, "Syntax error !\n");
		if (!root)
			ft_putstr_fd("Syntax error !\n", STDERR_FILENO);
		return (root);
	}
	tok = tks->content;
	if (!root)
		ft_putstr_fd("Syntax error !\n", STDERR_FILENO);
	if (tok->type != ENDT)
	{
		ft_fprintf(2, "Syntax error near `%s'\n", tok->str);
		modify_var(shell->env, "2");
	}
	return (root);
}
