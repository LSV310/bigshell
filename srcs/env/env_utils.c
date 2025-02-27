/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:51:52 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 14:50:46 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*get_env(t_mini *minishell, const char *var, size_t len)
{
	t_map	*current;

	current = minishell->env;
	while (current)
	{
		if (!ft_strncmp(current->key, var, max(len, ft_strlen(current->key))))
		{
			if (current->key[len] == 0)
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}
