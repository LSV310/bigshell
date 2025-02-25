/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:17:55 by agruet            #+#    #+#             */
/*   Updated: 2025/02/25 11:50:26 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_mini *minishell, char *var)
{
	t_list *new;

	new = ft_lstnew(var);
	if (!new)
		return (1);
	ft_lstadd_back(&minishell->env, new);
	return (0);
}
