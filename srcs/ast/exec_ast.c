/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 18:21:35 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/21 13:43:26 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	exec_ast(t_ast *ast, t_shell *shell)
{
	if (ast->type == ND_CMD)
		return (pipex(ast->cmds, shell));
	if (ast->type == ND_OR)
		return (exec_ast(ast->left, shell) || exec_ast(ast->right, shell));
	else if (ast->type == ND_AND)
		return (exec_ast(ast->left, shell) && exec_ast(ast->right, shell));
	else if (ast->type == ND_GRP)
		return (exec_ast(ast->left, shell));
	return (false);
}
