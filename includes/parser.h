/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:20:14 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 00:19:08 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum node_type
{
	ND_NULL = 0,
	ND_CMD,
	ND_AND,
	ND_OR,
	ND_GRP,
	ND_ERROR
}	t_node_type;

typedef struct s_cmd
{
	int		fdin;
	int		fdout;
	char	*name;
	char	**args;
}	t_cmd;

typedef struct s_ast	t_ast;

struct s_ast
{
	t_node_type	type;
	t_ast		*left;
	t_ast		*right;
	t_list		**cmds;
};

int		here_doc(char *delimiter, bool expand, t_shell *env);
t_list	*str_to_name_tks(const char *src, t_arena *arena);
void	skip_pipeline(t_list **tks);
t_ast	*parse_expr(t_list **tokens, t_arena *arena);
bool	token_heredoc(t_token *tok, t_shell *shell);

#endif
