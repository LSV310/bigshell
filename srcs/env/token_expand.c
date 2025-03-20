/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/20 00:50:23 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	switch_type_tk(t_list **cur, t_list **tks, t_shell *shell)
{
	t_token	*token;

	if (!tks || !(*cur))
		return (false);
	token = (*cur)->content;
	if (token->type == NAME)
		return (expand_namet(cur, tks, shell));
	else if (token->type == REDIN || token->type == REDOUT
		|| token->type == APPEN)
		return (expand_redt(*cur, *tks, shell));
	else
		return (token_fillstr((**cur).content, shell->arena));
}

int	expand_lst_token(t_list **tks, t_shell *shell)
{
	t_token	*token;
	t_list	*cur;

	cur = *tks;
	while (cur && cur->content)
	{
		token = cur->content;
		if (token->type == ENDT)
			break ;
		if (!switch_type_tk(&cur, tks, shell))
			return (false);
		cur = cur->next;
	}
	return (true);
}
