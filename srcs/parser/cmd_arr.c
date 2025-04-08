/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:07:49 by tgallet           #+#    #+#             */
/*   Updated: 2025/04/08 16:57:38 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	**flaten_tlistp(t_list *lst, t_arena *arena)
{
	const int	n = ft_lstsize(lst);
	int			i;
	void		**ptrs;

	ptrs = arena_calloc(arena, sizeof(void *) * (n + 1));
	if (!ptrs)
		return (NULL);
	ptrs[n] = NULL;
	i = 0;
	while (i < n && lst)
	{
		ptrs[i] = lst->content;
		lst = lst->next;
		i++;
	}
	ft_lstclear(&lst, void_content);
	return (ptrs);
}

t_list	*skip_cmd(t_list *tks)
{
	while(tks && tks->content && is_cmd_token(tks->content))
		tks = tks->next;
	return (tks);
}

bool	valid_pipeline(t_list *tks, bool after_pipe)
{
	bool	idk;
	t_token	*tk;

	if (!tks)
		return (false);
	tk = tks->content;
	if (is_cmd_token(tk))
		return (valid_pipeline(skip_cmd(tks), false));
	else if (tk->type == PIPE)
		return (valid_pipeline(tks->next, true));
	else
		return (!after_pipe);
}

t_list	**ptr_arr_pipeline(t_list *tks, t_arena *arena)
{
	t_list	*ptrs;

	ptrs = NULL;
	while (tks && tks->content && ((t_token *)tks->content)->type != ENDT)
	{
		if (tks && (!ptrs || (tks->content != ft_lstlast(ptrs)->content))
			&& is_cmd_token(tks->content))
			ft_lstadd_back(&ptrs, ar_lstnew(tks, arena));
		while (tks && tks->content && is_cmd_token(tks->content))
			tks = tks->next;
		if (!tks || !tks->content || (*(t_token *) tks->content).type != PIPE)
			break ;
		else
			tks = tks->next;
	}
	return ((t_list **)flaten_tlistp(ptrs, arena));
}


void	skip_pipeline(t_list **tks)
{
	t_token	*tk;

	while (1)
	{
		if (!tks || !*tks || !(*tks)->content)
			return ;
		tk = (*tks)->content;
		if (!(tk->type == PIPE || is_cmd_token(tk)))
			return ;
		*tks = (*tks)->next;
	}
}
