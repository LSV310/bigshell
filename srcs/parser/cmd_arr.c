/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:07:49 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/18 18:31:17 by tgallet          ###   ########.fr       */
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
	ptrs[n] = NULL;
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
			ft_lstadd_back(&ptrs, ft_lstnew(tks));
		while (tks && tks->content && is_cmd_token(tks->content))
			tks = tks->next;
	}
	return ((t_list	**)flaten_tlistp(ptrs, true));
}

static void	cmd_lst(t_list *tks)
{
	while (tks)
	{
		t_token	*tok = tks->content;
		if (!is_cmd_token(tok))
			break ;
		if (tok->p)
			printf("(%s) ", toktype_to_string(tok->type));
		else
			printf("NULL(%s)", toktype_to_string(tok->type));
		tks = tks->next;
	}
}

void	print_pipeline(t_list **pipeline)
{
	while (*pipeline)
	{
		cmd_lst(*pipeline);
		printf("\n");
		pipeline += 1;
	}
}
