/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:50:51 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/15 22:03:56 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char	*toktype_to_string(t_token_type type)
{
	if (type == ENDT)
		return ("END");
	else if (type == NAME)
		return ("NAME");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == ORT)
		return ("ORT");
	else if (type == ANDT)
		return ("ANDT");
	else if (type == REDIN)
		return ("REDIN");
	else if (type == REDOUT)
		return ("REDOUT");
	else if (type == APPEN)
		return ("APPEN");
	else if (type == LPAR)
		return ("LPAR");
	else if (type == RPAR)
		return ("RPAR");
	else
		return ("INVALID");
}

void	print_token(t_token tok, bool p_pointer)
{
	if (p_pointer)
	{
		if (tok.p)
			ft_printf("%.*s (%s)\n",
				(int)tok.len, tok.p, toktype_to_string(tok.type));
		else
			ft_printf("NULL (%s)\n", toktype_to_string(tok.type));
	}
	else
	{
		if (tok.str)
			ft_printf("%s (%s)\n", tok.str, toktype_to_string(tok.type));
		else
			ft_printf("NULL (%s)\n", toktype_to_string(tok.type));
	}
}

void	print_tokens(t_list *tks, bool p_pointer)
{
	while (tks)
	{
		print_token(*(t_token *)tks->content, p_pointer);
		tks = tks->next;
	}
}

// allocate and fill tok->str from tok->p without the quotes
int	token_fillstr(t_token *tok, t_arena	*arena)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (i < tok->len && tok->p[i])
		if (!char_in_set(tok->p[i++], "\"\'"))
			len++;
	tok->str = arena_alloc(len, arena);
	tok->str[len] = '\0';
	i = 0;
	len = 0;
	while (tok->str && i < tok->len && tok->p[i])
	{
		if (!char_in_set(tok->p[i], "\"\'"))
			tok->str[len++] = tok->p[i];
		i++;
	}
	return (tok->str != 0);
}

// TODO: use old token_fillstr and make sure it returns 0 when it fails
int	tks_fillstr(t_list *tks, t_shell *env)
{
	t_list	*cur;
	t_token	*tok;

	cur = tks;
	while (cur)
	{
		tok = cur->content;
		if (tok == NULL)
			return (0);
		if (tok->type == NAME || tok->type == REDIN
			|| tok->type == REDOUT || tok->type == APPEN)
			token_fillstr(tok, env->arena);
		else
			tok->str = ar_strndup(tok->p, tok->len, env->arena);
		cur = cur->next;
	}
	return (1);
}
