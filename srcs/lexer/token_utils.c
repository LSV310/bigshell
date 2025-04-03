/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:50:51 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/24 21:14:18 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*toktype_to_string(t_token_type type)
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
	else if (type == HEREDOC)
		return ("HEREDOC");
	else
		return ("INVALID");
}
