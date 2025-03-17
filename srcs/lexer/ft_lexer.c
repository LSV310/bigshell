/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:36:13 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/17 11:53:14 by agruet           ###   ########.fr       */
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

// return NULL on fail
t_list	*make_tokens(const char	*line_read, t_shell *env)
{
	t_list	*tks;

	tks = create_token_list(line_read, env->arena);
	print_tokens(tks, true);
	if (!valid_par(tks))
		return (NULL);
	if (!expand_lst_token(tks, env))
		return (NULL);
	print_tokens(tks, false);
	return (tks);
}

/* int	main(void)
{
	// const char	*input = "< note.txt echo *";
	const char	*input = "< note.txt echo";
	t_shell		*shell = test_env();
	t_list		*tks = make_tokens(input, shell);

	(void) tks;
	return (EXIT_SUCCESS);
} */
