/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:20:14 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/05 17:18:24 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum node_type
{
	ND_NULL = 0,
	ND_CMD,
	PIPELINE,
	ND_AND,
	ND_OR,
	ND_GRP
}	t_node_type;

typedef struct s_cmd
{
	int		fdin;
	char	*cmd;
	char	**args;
	int		fdout;
}	t_cmd;

typedef struct s_ast	t_ast;

struct s_ast
{
	t_node_type		type;
	t_ast			*left;
	t_ast			*right;
	t_cmd			**cmds;
};

int		here_doc(char *delimiter);

#endif
