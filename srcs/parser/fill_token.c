/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:24:47 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/16 15:42:26 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			return (false);
		if ((tok->type == NAME || tok->type == REDIN
			|| tok->type == REDOUT || tok->type == APPEN))
		{
			if (!token_fillstr(tok, env->arena))
				return (false);
		}
		else
			tok->str = ar_strndup(tok->p, tok->len, env->arena);
		cur = cur->next;
	}
	return (true);
}
