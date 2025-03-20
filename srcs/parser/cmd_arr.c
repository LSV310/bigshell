/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_arr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:07:49 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/20 01:10:49 by tgallet          ###   ########.fr       */
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
		return(NULL);
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

t_list	**ptr_arr_pipeline(t_list *tks, t_arena *arena)
{
	t_list	*ptrs;
	t_token	*tk;

	ptrs = NULL;
	while (tks && tks->content && !is_cmd_token(tks->content))
		tks = tks->next;
	while (tks && tks->content && ((t_token *)tks->content)->type != ENDT)
	{
		if (tks && (!ptrs || (tks->content != ft_lstlast(ptrs)->content))
				&& is_cmd_token(tks->content))
			ft_lstadd_back(&ptrs, ft_lstnew(tks));
		while (tks && tks->content && is_cmd_token(tks->content))
			tks = tks->next;
		tk = tks->content;
		if (!tk || tk->type != PIPE)
			break ;
		else
			tks = tks->next;
	}
	return ((t_list	**)flaten_tlistp(ptrs, arena));
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
		printf("consumed token: %s\n", toktype_to_string(tk->type));
		*tks = (*tks)->next;
	}
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
