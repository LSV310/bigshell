/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 13:44:38 by agruet            #+#    #+#             */
/*   Updated: 2025/04/17 13:26:02 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*advance_token(t_list **tokens)
{
	t_token	*tok;

	*tokens = (*tokens)->next;
	tok = (*tokens)->content;
	if (*tokens)
	{
		tok = (*tokens)->content;
		if (tok->type == ENDT)
			return (NULL);
		else
			return (tok);
	}
	else
	{
		ft_putstr_fd("parsing error: NULL token\n", STDERR_FILENO);
		return (NULL);
	}
}

bool	exec_ast(t_ast *ast, t_shell *shell)
{
	if (!ast || ast->type == ND_NULL)
		return (false);
	if (ast->type == ND_CMD)
	{
		if (!expand_lst_token(&ast->pipeline_start, shell))
		{
			ft_fprintf(2, "Invalid expand !\n");
			return (false);
		}
		return (!pipex(
				ptr_arr_pipeline(ast->pipeline_start, shell->arena),
				shell));
	}
	else if (ast->type == ND_OR)
		return (exec_ast(ast->left, shell) || exec_ast(ast->right, shell));
	else if (ast->type == ND_AND)
		return (exec_ast(ast->left, shell) && exec_ast(ast->right, shell));
	else if (ast->type == ND_GRP)
		return (exec_ast(ast->left, shell));
	else if (ast->type == ND_NULL)
		return (true);
	return (false);
}
