/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_tks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:31:03 by tgallet           #+#    #+#             */
/*   Updated: 2025/03/26 16:07:11 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*reverse_tks(t_list	*head)
{
	const t_list	*last = ft_lstlast(head);
	t_list			*cur;
	t_list			*next;
	t_list			*prev;

	if (!head || !head->next)
		return (head);
	cur = head;
	prev = (t_list *) last;
	while (cur != last)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	return (prev);
}

/*
int	main(void)
{
	t_list	a;
	t_list	b;
	t_list	c;
	t_list	d;

	a.content = "a";
	b.content = "b";
	c.content = "c";
	d.content = "d";
	a.next = &b;
	b.next = &c;
	c.next = &d;
	d.next = NULL;

	t_list	*pt = reverse_tks(&a);
	while (pt && pt->content)
	{
		printf("%s\n", (char *)pt->content);
		pt = pt->next;
	}
}
*/
