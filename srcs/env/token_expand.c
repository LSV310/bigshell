/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 19:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/14 17:45:15 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	switch_type_tk(t_list **cur, t_list **tks, t_shell *shell)
{
	t_token	*token;
	int		ret;

	if (!tks || !(*cur))
		return (false);
	token = (*cur)->content;
	if (token->type == NAME)
		return (expand_namet(cur, tks, shell));
	else if (token->type == REDIN || token->type == REDOUT
		|| token->type == APPEN)
		ret = expand_redt(*cur, shell);
	else if (token->type == HEREDOC)
		ret = token_heredoc((**cur).content, shell);
	else
		ret = token_fillstr((**cur).content, shell->arena);
	*cur = (*cur)->next;
	return (ret);
}

int	expand_lst_token(t_list **tks, t_shell *shell)
{
	t_token	*token;
	t_list	*cur;

	cur = *tks;
	while (cur && cur->content)
	{
		token = cur->content;
		if (token->type == ENDT || token->type == ANDT || token->type == ORT)
			break ;
		if (!switch_type_tk(&cur, tks, shell))
			return (false);
	}
	return (true);
}
