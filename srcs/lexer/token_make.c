/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_make.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:38:10 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/18 13:06:39 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	special_token_cpy(t_lexer *lex, t_token *tok, t_token cpy)
{
	if (cpy.type == APPEN || cpy.type == HEREDOC
		|| cpy.type == REDIN || cpy.type == REDOUT)
	{
		lex->cur += cpy.len;
		if (lex->cur - lex->start >= lex->len)
		{
			tok->type = INVALID;
			return ;
		}
		skip_spaces(lex);
		fill_token(lex, tok, cpy.type);
	}
	else
	{
		tok->p = lex->cur;
		tok->len = cpy.len;
		tok->type = cpy.type;
		lex->cur += cpy.len;
	}
}

void	special_token(t_lexer *lex, t_token *tok)
{
	const t_token	specials[] = {
	{.p = ">>", .type = APPEN, .len = 2},
	{.p = "<<", .type = HEREDOC, .len = 2},
	{.p = "||", .type = ORT, .len = 2},
	{.p = "&&", .type = ANDT, .len = 2},
	{.p = "|", .type = PIPE, .len = 1},
	{.p = "<", .type = REDIN, .len = 1},
	{.p = ">", .type = REDOUT, .len = 1},
	{.p = "(", .type = LPAR, .len = 1},
	{.p = ")", .type = RPAR, .len = 1}
	};
	int				i;

	i = 0;
	while (i < sizeof(specials) / sizeof(t_token))
	{
		if (ft_strncmp(lex->cur, specials[i].p, ft_strlen(specials[i].p)) == 0)
			return (special_token_cpy(lex, tok, specials[i]));
		i++;
	}
	return (bad_token(lex, tok));
}

t_token	*get_next_token(t_lexer *lex, t_arena *arena)
{
	t_token	*tok;

	tok = arena_calloc(arena, sizeof(t_token));
	if (!tok)
		return (NULL);
	skip_spaces(lex);
	if (*lex->cur == '\0' || (lex->cur >= lex->start + lex->len))
		make_end_token(lex, tok);
	else if (!char_in_set(*lex->cur, "|&<>()"))
		fill_token(lex, tok, NAME);
	else
		special_token(lex, tok);
	return (tok);
}

t_list	*create_token_list(const char *src, t_arena *arena)
{
	t_list		*tks;
	t_token		*tmp;
	t_lexer		lex;

	lex = init_lexer(src);
	tks = NULL;
	while (true)
	{
		tmp = get_next_token(&lex, arena);
		ft_lstadd_back(&tks, ar_lstnew(tmp, arena));
		if (!tks || !tmp)
			return (NULL);
		if (tmp->type == ENDT || tmp->type == INVALID)
			break ;
	}
	return (tks);
}
