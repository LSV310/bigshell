/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:51:53 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 21:21:40 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_wildcard(t_token *tok, char *res)
{
	char	*wild;
	char	*new_res;

	wild = get_wildcards(tok->str, BOTH, false);
	free(tok->str);
	tok->str = res;
	new_res = ft_strjoin(tok->str, wild);
	free(wild);
	free(tok->str);
	tok->str = new_res;
	new_res = ft_strjoin(tok->str, " ");
	free(tok->str);
	return (new_res);
}

char	*name_wild(t_lexer lex)
{
	t_token	tok;
	char	*res;

	if (!lex.start)
		return (NULL);
	res = ft_strdup("");
	while (res)
	{
		ft_memset(&tok, 0, sizeof(t_token));
		fill_token(skip_spaces(&lex), &tok, NAME);
		tok.str = ft_substr(tok.p, 0, tok.len);
		if (!tok.str || !tok.len)
		{
			free(tok.str);
			break ;
		}
		res = process_wildcard(&tok, res);
	}
	free((char *)lex.start);
	return (res);
}

bool	expand_namet(t_list **cur, t_list **tks, t_shell *shell)
{
	char	*res;
	t_token	*tok;
	t_list	*new_tks;
	t_list	*new_cur;

	tok = (*cur)->content;
	res = env_exp(ft_substr(tok->p, 0, tok->len), shell);
	res = name_wild(init_lexer(res));
	new_tks = str_to_name_tks(res, shell->arena);
	if (new_tks)
	{
		new_cur = ft_lstlast(new_tks);
		lst_insert((*cur), new_tks);
		new_cur = new_cur->next;
	}
	else
		new_cur = (*cur)->next;
	arlst_remove_node(tks, (*cur));
	*cur = new_cur;
	free(res);
	return (true);
}

char	*red_wild(char *src)
{
	char	*res;

	res = get_wildcards(src, FILES, true);
	free(src);
	if (!res)
	{
		ft_printf("*: zi redirect ize ambigousse\n");
		return (NULL);
	}
	return (res);
}

bool	expand_redt(t_list *cur, t_shell *shell)
{
	char	*res;
	t_token	*tok;

	tok = cur->content;
	res = env_exp(ft_substr(tok->p, 0, tok->len), shell);
	res = red_wild(res);
	if (!res)
		return (false);
	tok->p = res;
	tok->len = ft_strlen(res);
	if (!token_fillstr(tok, shell->arena))
	{
		free(res);
		return (false);
	}
	free(res);
	return (true);
}
