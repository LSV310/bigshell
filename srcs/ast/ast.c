/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 23:41:03 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/08 16:12:06 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*create_node(t_node_type type,
	t_list **tokens, t_arena *arena, t_ast *childs[2])
{
	t_ast	*node;

	node = arena_calloc(arena, sizeof(t_ast));
	if (!node)
		return (NULL);
	node->type = type;
	if (!tokens_to_pipeline(tokens, arena, node))
		return (NULL);
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
	if (!ret)
		return (NULL);
	tok = (**tokens).content;
	if (tok->type != RPAR)
	{
		ft_putstr_fd("syntax error: \
expected right parenthesis\n", 2);
		return (NULL);
	}
	advance_token(tokens);
	return (ret);
}

t_ast	*parse_something(t_list **tokens, t_arena *arena)
{
	t_token	*tok;

	if (!tokens || !*tokens || !(**tokens).content)
		return (NULL);
	tok = (**tokens).content;
	if (tok->type == LPAR)
		return (parse_par(tokens, arena));
	else if (is_cmd_token(tok))
		return (create_node(ND_CMD, tokens, arena, (t_ast *[2]){NULL, NULL}));
	else
		return (NULL);
}

t_ast	*parse_expr(t_list **tokens, t_arena *arena)
{
	t_ast	*left;
	t_token	*tok;
	t_ast	*right;

	left = parse_something(tokens, arena);
	while (tokens && *tokens && (**tokens).content && left)
	{
		tok = (**tokens).content;
		if (tok->type == ANDT || tok->type == ORT)
		{
			advance_token(tokens);
			right = parse_something(tokens, arena);
			if (tok->type == ANDT)
				left = create_node(ND_AND, NULL, arena,
						(t_ast *[2]){left, right});
			else
				left = create_node(ND_OR, NULL, arena,
						(t_ast *[2]){left, right});
		}
		else
			break ;
	}
	return (left);
}

t_ast	*build_ast(t_list *tks, t_shell *shell)
{
	t_ast	*root;
	t_token	*tok;

	if (!tks || !tks->content)
		return (NULL);
	tok = tks->content;
	if (tok->type == ENDT)
		return (NULL);
	root = parse_expr(&tks, shell->arena);
	tok = tks->content;
	if (!tks || !tks->content || !root
		|| ((t_token *)tks->content)->type != ENDT)
	{
		ft_fprintf(2, "Syntax error !\n");
		modify_var(shell->env, "2");
	}
	return (root);
}
