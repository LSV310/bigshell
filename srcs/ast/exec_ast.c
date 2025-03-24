/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:44:38 by agruet            #+#    #+#             */
/*   Updated: 2025/03/24 20:33:59 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	advance_token(t_list **tokens)
{
	t_token	*tok;

	tok = (*tokens)->content;
	*tokens = (*tokens)->next;
	tok = (*tokens)->content;
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

bool	exec_ast(t_ast *ast, t_shell *shell)
{
	if (ast->type == ND_CMD)
		return (!pipex(ast->cmds, shell));
	if (ast->type == ND_OR)
		return (exec_ast(ast->left, shell) || exec_ast(ast->right, shell));
	else if (ast->type == ND_AND)
		return (exec_ast(ast->left, shell) && exec_ast(ast->right, shell));
	else if (ast->type == ND_GRP)
		return (exec_ast(ast->left, shell));
	else if (ast->type == ND_NULL)
		return (true);
	return (false);
}
