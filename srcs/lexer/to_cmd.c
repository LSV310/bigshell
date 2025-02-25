/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:03:42 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/25 16:02:50 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_par(t_dlltok *tks)
{
	int	open_par;

	open_par = 0;
	while (tks && tks->token->type != ENDT)
	{
		if (tks->token->type == LPAR)
			open_par++;
		else if (tks->token->type == RPAR)
			open_par--;
		if (open_par < 0)
			return (false);
		tks = tks->next;
	}
	if (open_par == 0)
		return (true);
	return (false);
}
