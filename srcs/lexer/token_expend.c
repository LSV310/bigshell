/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/26 18:03:08 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_envar(const char *cur, int *i)
{
	size_t	len;
	size_t	n;

	n = 0;
	(*i)++;
	while (cur[*i] && !char_in_set(cur[*i], "\"$&|<>()# "))
	{
		(*i)++;
		n++;
	}
	if (n == 0)
		return (0);
	len = ft_strlen(get_env_variable(cur + *i - n, n, NULL));
	return (len);
}

size_t	tokenstr_size(t_token *tok)
{
	size_t	n;
	int		i;
	char	quote;

	i = 0;
	n = 0;
	quote = 0;
	while (i < tok->len)
	{
		if (!quote && char_in_set(tok->p[i], "\"'"))
			quote = tok->p[i];
		else if (tok->p[i] == quote)
			quote = 0;
		else if ((!quote || quote == '"') && tok->p[i] == '$')
			n += size_envar(tok->p, &i);
		else
			n++;
		i++;
	}
	return (n);
}

void	write_envar(char *here, const char *cur, int *i)
{
	size_t		len;
	size_t		n;
	const char	*envar;

	n = 0;
	(*i)++;
	while (cur[*i] && !char_in_set(cur[*i], "\"$&|<>()# "))
	{
		(*i)++;
		n++;
	}
	envar = get_env_variable(cur, n, NULL);
	ft_memcpy(here, envar, ft_strlen(envar));
}

void	expend_token_fill(t_token *tok, size_t len, int i, char quote)
{
	int	j;

	j = 0;
	while (i < tok->len && j < len)
	{
		if (!quote && char_in_set(tok->p[i], "\"'"))
			quote = tok->p[i];
		else if (tok->p[i] == quote)
			quote = 0;
		else if ((!quote || quote == '"') && tok->p[i] == '$')
			write_envar(tok->str + j, tok->p + i, &i);
		else
			tok->str[j] = tok->str[i];
		i++;
	}
}

int	expend_token(t_token *tok, t_arena *arena)
{
	size_t	len;

	len = tokenstr_size(tok);
	tok->str = arena_alloc(len, arena);
	if (!tok->str)
		return (0);
	tok->str[len] = 0;
	expend_token_fill(tok, len, 0, 0);
	return (1);
}

int	token_transform(t_list *tks, t_arena *arena)
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
			expend_token(tok, arena);
		else
			tok->str = ar_strndup(tok->p, tok->len, arena);
		cur = cur->next;
	}
	return (1);
}
