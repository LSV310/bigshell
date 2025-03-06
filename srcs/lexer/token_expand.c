/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/06 19:45:46 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_envar(const char *cur, int *i, t_mini *env)
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
	if (n == 0)
		return (0);
	envar = get_env(env, cur + *i - n, n)->value;
	len = ft_strlen(envar);
	return (len);
}

size_t	write_envar(char *here, const char *cur, int *i, t_mini *env)
{
	size_t		len;
	size_t		n;
	const char	*envar;
	size_t		envar_len;

	n = 0;
	(*i)++;
	while (cur[*i] && !char_in_set(cur[*i], "\"$&|<>()# "))
	{
		(*i)++;
		n++;
	}
	envar = get_env(env, cur + *i - n, n)->value;
	envar_len = ft_strlen(envar);
	ft_memcpy(here, envar, ft_strlen(envar));
	return (envar_len);
}

void	expend_token_fill(t_token *tok, size_t len, t_mini *env)
{
	int		j;
	int		i;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (i < tok->len && j < len)
	{
		if (!quote && char_in_set(tok->p[i], "\"'"))
			quote = tok->p[i];
		else if (tok->p[i] == quote)
		quote = 0;
		else if ((!quote || quote == '"') && tok->p[i] == '$')
			j += write_envar(tok->str + j, tok->p, &i, env);
		else
			tok->str[j++] = tok->p[i++];
	}
}

size_t	tokenstr_size(t_token *tok, t_mini *env)
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
			n += size_envar(tok->p, &i, env);
		else
		{
			n++;
			i++;
		}
	}
	return (n + 1);
}

int	expend_token(t_token *tok, t_arena *arena, t_mini *env)
{
	size_t	len;

	len = tokenstr_size(tok, env);
	tok->str = arena_alloc(len, arena);
	if (!tok->str)
		return (0);
	tok->str[len] = 0;
	expend_token_fill(tok, len, env);
	return (1);
}
