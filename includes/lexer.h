/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:30:56 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/25 23:16:03 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"
# include "arena.h"

typedef enum type_token
{
	INVALID = 0,
	NAME,
	PIPE,
	ORT,
	ANDT,
	REDIN,
	REDOUT,
	APPEN,
	LPAR,
	RPAR,
	HEREDOC,
	ENDT
}	t_token_type;

typedef struct s_lexer
{
	const char	*start;
	const char	*cur;
	size_t		len;
}	t_lexer;

typedef struct s_token
{
	const char		*p;
	size_t			len;
	t_token_type	type;
	char			*str;
}	t_token;

typedef struct s_cmd
{
	char	*file_in;
	char	*cmd;
	char	**args;
	char	*file_out;
}	t_cmd;

int		is_special(char c);
void	print_token(t_token tok);
void	print_tokens(t_list *tks);
t_lexer	init_lexer(char *rdl);
void	skip_spaces(t_lexer *lex);
void	fill_token(t_lexer *lex, t_token *tok, t_token_type type);
void	make_end_token(t_lexer *lex, t_token *tok);
void	bad_token(t_lexer *lex, t_token *tok);
int		valid_par(t_list *tks);
t_list	*context_free_tokens(t_lexer *lex, t_arena *arena);

#endif
