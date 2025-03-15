/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_exp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:51:53 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/14 18:49:21 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*name_wild(t_lexer lex, t_shell *shell) // must keep the quotes
{
	char	*wild;
	t_token	tok;
	char	*res;

	if (!lex.start)
		return (NULL);
	res = ft_strdup("");
	while (res)
	{
		memset(&tok, 0, sizeof(t_token));
		fill_token(skip_spaces(&lex), &tok, NAME);
		tok.str = ft_substr(tok.p, 0, tok.len);
		if (!tok.str)
			break ;
		wild = get_wildcards(tok.str , BOTH, false);
		free(tok.str);
		tok.str = res;
		res = ft_strjoin(tok.str, wild);
		free(wild);
		free(tok.str);
		tok.str = res;
		res = ft_strjoin(tok.str, " ");
		free(tok.str);
	}
	return (res);
}

bool	expand_namet(t_list *cur, t_list *tks, t_shell *shell)
{
	char	*res;
	t_token	*tok;
	t_list	*new_tks;

	tok = cur->content;
	res = env_exp(ft_substr(tok->p, 0, tok->len), shell);
	res = name_wild(init_lexer(res), shell);
	lst_insert(cur, str_to_name_tks(res, shell->arena));
	lst_remove_node(&tks, cur, void_content);
	if (!tks_fillstr(tks, shell))
	{
		free(res);
		return (false);
	}
	free(res);
	return (true);
}

char	*red_wild(char *src, t_shell *shell, t_token_type t_type) // must keep the quotes
{
	char	*res;

	res = get_wildcards(src, FILES, true);
	if (!res)
		ft_printf("*: zi redirect ize ambigousse\n");
	free(src);
	return (res);
}

bool	expand_redt(t_list *cur, t_list *tks, t_shell *shell)
{
	char	*res;
	t_token	*tok;
	t_list	*new_tks;

	tok = cur->content;
	res = env_exp(ft_substr(tok->p, 0, tok->len), shell);
	res = red_wild(res, shell, tok->type);
	if (!token_fillstr(tok, shell->arena))
	{
		free(res);
		return (false);
	}
	free(res);
	return (true);
}
