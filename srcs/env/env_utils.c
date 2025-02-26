/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:51:52 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 14:58:19 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*get_env(t_mini *minishell, char *var, size_t len)
{
	t_map	*current;

	current = minishell->env;
	while (current)
	{
		if (!ft_strncmp(current->key, var, len))
			return (current);
		current = current->next;
	}
	return (NULL);
}
