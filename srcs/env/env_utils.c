/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgallet <tgallet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:51:52 by agruet            #+#    #+#             */
/*   Updated: 2025/02/27 18:37:59 by tgallet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_map	*get_env(t_mini *minishell, const char *var, size_t len)
{
	t_map	*current;

	current = minishell->env;
	while (current)
	{
		if (!ft_strncmp(current->key, var, len))
		{
			if (current->key[len] == 0)
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}
