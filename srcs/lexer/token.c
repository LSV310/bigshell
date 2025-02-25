/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:50:51 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/25 16:01:43 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

const char	*toktype_to_string(token_type type)
{
	if (type == ENDT)
		return ("END");
	else if (type == NAME)
		return ("NAME");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == ORT)
		return ("ORT");
	else if (type == ANDT)
		return ("ANDT");
	else if (type == REDIN)
		return ("REDIN");
	else if (type == REDOUT)
		return ("REDOUT");
	else if (type == APPEN)
		return ("APPEN");
	else if (type == LPAR)
		return ("LPAR");
	else if (type == RPAR)
		return ("RPAR");
	else
		return ("INVALID");
}

void	print_token(t_token tok)
{
	if (tok.p)
		printf("%.*s (%s)\n", (int)tok.len, tok.p, toktype_to_string(tok.type));
	else
		printf("NULL (%s)\n", toktype_to_string(tok.type));
}

void	print_tokens(t_dlltok *tks)
{
	while (tks)
	{
		print_token(*tks->token);
		tks = tks->next;
	}
}
