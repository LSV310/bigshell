/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:54:02 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 15:04:21 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_par(t_list *tks)
{
	int	open_par;

	open_par = 0;
	while (tks && ((t_token *)tks->content)->type != ENDT)
	{
		if (((t_token *)tks->content)->type == LPAR)
			open_par++;
		else if (((t_token *)tks->content)->type == RPAR)
			open_par--;
		if (open_par < 0)
			return (false);
		tks = tks->next;
	}
	if (open_par == 0)
		return (true);
	return (false);
}

bool	valid_tks(t_list *tks)
{
	t_token	*tok;

	while (1)
	{
		if (!tks || !tks->content)
		{
			ft_putstr_fd("tokenization error\n", 2);
			return (false);
		}
		tok = tks->content;
		if (tok->type == ENDT)
			break ;
		if (tok->len == 0 && (tok->type == HEREDOC || tok->type == APPEN
			|| tok->type == REDIN || tok->type == REDOUT))
		{
			ft_putstr_fd("redirect without arguments\n", 2);
			return (false);
		}
		tks = tks->next;
	}
	return (true);
}

bool	check_tks(t_list *tks)
{
	if (!valid_tks(tks) || !valid_par(tks))
		return (false);
}
