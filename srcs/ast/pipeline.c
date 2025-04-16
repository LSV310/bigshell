/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:27:21 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/16 18:44:00 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	tokens_to_pipeline(t_list **tks, t_ast *node)
{
	if (!tks)
	{
		node->pipeline_start = NULL;
		return (true);
	}
	if (is_cmd_token((**tks).content) && valid_pipeline(*tks, false))
	{
		node->pipeline_start = *tks;
		skip_pipeline(tks);
		return (true);
	}
	else
		return (false);
}

int	count_cmd(t_list *tks)
{
	t_token	*tk;
	int		n;

	n = 1;
	while (tks && tks->content)
	{
		tk = tks->content;
		if (tk->type == ORT || tk->type == ANDT || tk->type == RPAR
			|| tk->type == ENDT)
			break ;
		if (tk->type == PIPE)
			n++;
	}
	return (n);
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
