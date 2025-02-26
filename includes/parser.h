/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:20:14 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/26 16:51:25 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef enum node_type
{
	ND_CMD,
	PIPELINE,
	ND_AND,
	ND_OR,
	ND_GRP
}	t_node_type;

typedef struct s_cmd
{
	char	*file_in;
	char	*cmd;
	char	**args;
	char	*file_out;
}	t_cmd;

typedef struct s_ast
{
	t_node_type		type;
	char			**command;
	size_t			n_childs;
	struct s_ast	**childs;

}	t_ast;

#endif
