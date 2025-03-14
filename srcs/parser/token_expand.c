/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/13 20:33:03 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*wildcard_expand(t_lexer lex, t_shell *shell) // must keep the quotes
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
	// TODO: delete token case, multi token case, env expand + wildcard expand
	char	*res;
	t_token	*tok;
	t_list	*new_tks;

	tok = cur->content;
	res = env_exp(ft_substr(tok->p, 0, tok->len), shell);
	if (!res)
		lst_remove_node(&tks, cur, void_content);
	res = wildcard_expand(init_lexer(res), shell);
	free(res);
	return (true);
}

int	expand_lst_token(t_list *tks, t_shell *shell)
{
	t_token	*token;
	t_list	*cur;

	cur = tks;
	while (cur && cur->content)
	{
		token = cur->content;
		if (token->type == ENDT)
			break ;
		else if (token->type == NAME)
		{
			if (!expand_namet(cur, tks, shell))
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}
