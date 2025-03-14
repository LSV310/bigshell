/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:07:49 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/14 13:51:34 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	**flaten_tlistp(t_list *lst, bool do_free)
{
	const int	n = ft_lstsize(lst);
	int			i;
	void		**ptrs;

	ptrs = ft_calloc(n + 1, sizeof(void *));
	if (!ptrs)
		return(NULL);
	i = 0;
	while (i < n && lst)
	{
		ptrs[i] = lst->content;
		lst = lst->next;
		i++;
	}
	if (do_free)
		ft_lstclear(&lst, void_content);
	return (ptrs);
}

t_list	**ptr_arr_pipeline(t_list *tks)
{
	t_list	*ptrs;
	t_token	*tk;

	ptrs = NULL;
	while (tks && tks->content && ((t_token *)tks->content)->type != ENDT)
	{
		while (tks && tks->content && !is_cmd_token(tks->content))
			tks = tks->next;
		if (tks && (!ptrs || (tks->content != ft_lstlast(ptrs)->content)))
			ft_lstadd_back(&ptrs, ft_lstnew(tks->content));
		while (tks && tks->content && is_cmd_token(tks->content))
			tks = tks->next;
	}
	return ((t_list	**)flaten_tlistp(ptrs, true));
}
