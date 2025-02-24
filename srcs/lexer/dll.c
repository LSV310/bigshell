/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:07:44 by tgallet           #+#    #+#             */
/*   Updated: 2025/02/21 14:14:52 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_dll(t_dlltok **head)
{
	t_dlltok	*tmp;
	t_dlltok	*next;

	tmp = *head;
	while (tmp)
	{
		next = tmp->next;
		free(tmp->token);
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

// double linked list add
void	dll_addback(t_dlltok **head, t_token *new)
{
	t_dlltok	*tmp;

	if (*head == NULL)
	{
		*head = malloc(sizeof(t_dlltok));
		(*head)->token = new;
		(*head)->prev = NULL;
		(*head)->next = NULL;
	}
	else
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = malloc(sizeof(t_dlltok));
		if (!tmp->next)
			return (free_dll(head));
		tmp->next->token = new;
		tmp->next->prev = tmp;
		tmp->next->next = NULL;
	}
}
