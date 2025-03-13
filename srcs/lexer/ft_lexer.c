/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:36:13 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/13 18:35:37 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_par(t_list *tks)
{
	int	open_par;

	open_par = 0;
	while (tks && ((t_token *)tks->content)->type != ENDT)
	{
		if (((t_token *)tks->content)->type == LPAR)
			open_par++;
		else if (((t_token *)tks->content)->type == RPAR)
			open_par--;
		if (open_par < 0)
			return (false);
		tks = tks->next;
	}
	if (open_par == 0)
		return (true);
	return (false);
}

t_lexer	init_lexer(const char *rdl)
{
	t_lexer	lex;

	lex.start = rdl;
	lex.cur = rdl;
	lex.len = ft_strlen(rdl);
	return (lex);
}

t_lexer	*skip_spaces(t_lexer *lex)
{
	while (ft_isspace(*lex->cur))
		lex->cur++;
	return (lex);
}

t_list	*make_tokens(const char	*line_read, t_arena *arena, t_shell *env)
{
	t_list	*tks;
	t_lexer	lex;

	lex = init_lexer(line_read);
	tks = init_tokens(&lex, arena);
	if (!valid_par(tks))
		ft_printf("bad parenthesis\n");
	expend_token_list(tks, arena, env);
	print_tokens(tks, false);
	return (tks);
}
