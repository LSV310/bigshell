/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 15:24:47 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/18 12:52:26 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	strlen_noquotes(const char *p, size_t len)
{
	size_t	new_len;
	size_t	i;

	i = 0;
	new_len = 0;
	while (i < len && p[i])
	{
		if (!char_in_set(p[i], "\"\'"))
			new_len++;
		i++;
	}
	return (new_len + 1);
}

void	strcpy_noquotes(char *dest, const char *src, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < len && src[i])
	{
		if (!char_in_set(src[i], "\"\'"))
			dest[j++] = src[i];
		i++;
	}
	dest[j] = '\0';
}

int	token_fillstr(t_token *tok, t_arena *arena)
{
	size_t	len;

	len = strlen_noquotes(tok->p, tok->len);
	tok->str = arena_alloc(len, arena);
	if (!tok->str)
		return (0);
	strcpy_noquotes(tok->str, tok->p, tok->len);
	return (1);
}

// TODO: use old token_fillstr and make sure it returns 0 when it fails
int	tks_fillstr(t_list *tks, t_arena *arena)
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
			if (!token_fillstr(tok, arena))
				return (false);
		}
		else
			tok->str = ar_strndup(tok->p, tok->len, arena);
		cur = cur->next;
	}
	print_tokens(tks, false);
	return (true);
}
