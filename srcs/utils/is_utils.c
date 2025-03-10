/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:28:56 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/08 13:44:38 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	char_in_set(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int	is_special(char c)
{
	return (char_in_set(c, "|<>&()"));
}

int	is_cmd_token(t_token *tok)
{
	if (!tok)
		return (0);
	if (tok->type == NAME || tok->type == REDIN || tok->type == APPEN
		|| tok->type == HEREDOC || tok->type == REDOUT)
		return (1);
	else
		return (0);
}
