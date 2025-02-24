/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:30:56 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/24 12:56:01 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "minishell.h"

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
} token_type;

typedef struct s_lexer
{
	const char	*start;
	const char	*cur;
	size_t		len;
} t_lexer;

typedef struct s_token
{
	const char	*p;
	size_t		len;
	token_type	type;
}	t_token;

typedef struct s_dlltok
{
	t_token			*token;
	struct s_dlltok	*prev;
	struct s_dlltok *next;
}	t_dlltok;

void	dll_addback(t_dlltok **head, t_token *new);
int		is_special(char c);
void	print_token(t_token tok);
void	print_tokens(t_dlltok *tks);
t_lexer	init_lexer(char *rdl);
void	skip_spaces(t_lexer *lex);
void	fill_token(t_lexer *lex, t_token *tok, token_type type);
void	make_end_token(t_lexer *lex, t_token *tok);
void	bad_token(t_lexer *lex, t_token *tok);

#endif
