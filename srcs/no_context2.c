/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_context2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:38:10 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/24 12:56:58 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_lexer	init_lexer(char *rdl)
{
	t_lexer	lex;

	lex.start = rdl;
	lex.cur = rdl;
	lex.len = ft_strlen(rdl);
	return (lex);
}
void	skip_spaces(t_lexer *lex)
{
	while (ft_isspace(*lex->cur))
		lex->cur++;
}

void	fill_token(t_lexer *lex, t_token *tok, token_type type)
{
	char	quote;

	quote = 0;
	tok->p = lex->cur;
	tok->type = type;
	while (*lex->cur != '\0' && (quote != 0 || !ft_isspace(*lex->cur)))
	{
		if (quote == 0 && char_in_set(*lex->cur, "\"\'"))
			quote = *lex->cur;
		else if (quote == *lex->cur)
			quote = 0;
		tok->len++;
		lex->cur++;
	}
}

void	make_end_token(t_lexer *lex, t_token *tok)
{
	tok->type = ENDT;
	tok->len = 0;
	tok->p = lex->cur;
}

void	bad_token(t_lexer *lex, t_token *tok)
{
	tok->p = lex->cur;
	tok->type = INVALID;
	while (*lex->cur && !ft_isspace(*lex->cur))
	{
		tok->len++;
		lex->cur++;
	}
}
