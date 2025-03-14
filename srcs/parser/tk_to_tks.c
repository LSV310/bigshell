/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tk_to_tks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 20:15:12 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/14 14:28:55 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_next_nametk(t_lexer *lex, t_arena *arena)
{
	t_token	*tok;

	tok = arena_calloc(arena, sizeof(t_token));
	if (!tok)
		return (NULL);
	skip_spaces(lex);
	if (*lex->cur == '\0' || (lex->cur >= lex->start + lex->len))
		make_end_token(lex, tok);
	else
		fill_token(lex, tok, NAME);
	return (tok);
}

t_list	*str_to_name_tks(const char *src, t_arena *arena)
{
	t_list		*tks;
	t_token		*tmp;
	t_lexer		lex;

	if (!src)
		return (NULL);
	lex = init_lexer(src);
	tks = NULL;
	while (true)
	{
		tmp = get_next_nametk(&lex, arena);
		ft_lstadd_back(&tks, ar_lstnew(tmp, arena));
		if (!tks || !tmp)
			return (NULL);
		if (tmp->type == ENDT || tmp->type == INVALID)
			break ;
	}
	return (tks);
}

void	lst_insert(t_list *dest, t_list *to_insert)
{
	t_list	*tmp;

	if (!dest || !to_insert)
		return ;
	tmp = dest->next;
	dest->next = to_insert;
	ft_lstlast(to_insert)->next = tmp;
}
