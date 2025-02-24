/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_context.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 12:38:10 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/24 00:27:37 by tgallet          ###   ########.fr       */
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

void	fill_token(t_lexer *lex, t_token *tok)
{
	char	quote;

	quote = 0;
	tok->p = lex->cur;
	tok->type = NAME;
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

t_token	*get_next_token(t_lexer *lex)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(t_token));
	if (!tok)
		return (NULL);
	skip_spaces(lex);
	if (*lex->cur == '\0' || (lex->cur >= lex->start + lex->len))
		make_end_token(lex, tok);
	else if (!char_in_set(*lex->cur, "|&<>"))
		fill_token(lex, tok);
	else
		bad_token(lex, tok);
	return (tok);
}

t_dlltok *context_free_tokens(t_lexer *lex)
{
	t_dlltok	*tks;
	t_token		*tmp;

	tks = NULL;
	while (1)
	{
		tmp = get_next_token(lex);
		dll_addback(&tks, tmp);
		if (!tks)
			return (NULL);
		if (tmp->type == ENDT)
			break ;
	}
	print_tokens(tks);
	return (tks);
}

int	main(int ac, char *av[])
{
	if (ac == 2)
	{
		t_lexer	lex;

		lex = init_lexer(av[1]);
		context_free_tokens(&lex);
	}
}
