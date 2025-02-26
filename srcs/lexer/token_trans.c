/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_trans.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/25 22:57:10 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	size_envar(const char *cur, int *i)
{
	size_t	len;
	size_t	n;
	char	*tmp;

	n = 0;
	while (cur[n] && !char_in_set(cur[n], "\"$&|<>()"))
		n++;
	tmp = malloc(n + 1);
	if (!tmp)
		return (0);
	tmp[n] = 0;
	ft_memcmp(cur, tmp, n);
	len = ft_strlen(get_env_variable(tmp, NULL));
	return (len);
}

size_t	alloc_tokenstr(t_token *tok)
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
		else
			n++;
		if ((!quote || quote == '"') && tok->p[i] == '$')
			n += size_envar(tok->p, &i);
		i++;
	}
	return (n);
}

void	quoting(t_token *tok)
{
	char	quote;
	int		i;

	i = 0;
	while (i < tok->len)
	{

	}
}

void	token_transform(t_list *tks)
{
	t_list	*cur;

	cur = tks;
	while (cur)
	{
		quoting(cur->content);
		cur = cur->next;
	}
}
