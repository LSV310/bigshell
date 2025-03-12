/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/12 21:38:08 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*wildcard_expand(char *src, t_shell *shell);

t_token	*get_next_nametk(t_lexer *lex, t_arena *arena)
{
	t_token	*tok;

	tok = arena_calloc(arena, sizeof(t_token));
	if (!tok)
		return (NULL);
	tok->arena = arena;
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

bool	expand_namet(t_list *cur, t_list *tks, t_shell *shell)
{
	// TODO: delete token case, multi token case, env expand + wildcard expand
	char	*res;
	t_token	*tok;
	t_list	*new_tks;

	tok = cur->content;
	res = env_exp(ft_substr(tok->p, 0, tok->len), shell);
	if (!res || !*res)
		lst_remove_node(&tks, cur, void_content);
	res = wildcard_expand(res, shell);
	free(res);
	return (true);
}

int	expand_lst_token(t_list *tks, t_shell *shell)
{
	t_token	*token;
	t_list	*cur;

	cur = tks;
	while (cur && cur->content)
	{
		token = cur->content;
		if (token->type == ENDT)
			break ;
		else if (token->type == NAME)
		{
			if (!expand_namet(cur, tks, shell))
				return (0);
		}
		cur = cur->next;
	}
}
