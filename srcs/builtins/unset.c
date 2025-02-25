/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:31:31 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 12:23:39 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(t_mini *minishell, char *var)
{
	t_list *current;

	if (ft_strchr(var, '='))
		return (1);
	current = minishell->env;
	while (current)
	{
		if (!ft_strncmp((char *)current->content, var,
			ft_strchr((char *)current->content, '=') - (char *)current->content))
			return (lst_remove_node(&minishell->env, current, &free_content), 0);
		current = current->next;
	}
	return (1);
}
