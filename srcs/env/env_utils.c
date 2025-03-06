/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:51:52 by agruet            #+#    #+#             */
/*   Updated: 2025/03/06 15:35:50 by agruet           ###   ########.fr       */
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

char	**convert_env(t_map *map)
{
	size_t	size;
	size_t	i;
	char	**tab;
	char	*temp;

	size = ft_mapsize(map);
	tab = calloc(size + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (map)
	{
		temp = ft_strjoin(map->key, "=");
		if (!temp)
			return (free_tab(tab, i), NULL);
		tab[i] = ft_strjoin(temp, map->value);
		if (!tab[i])
			return (free(temp), free_tab(tab, i), NULL);
		i++;
		map = map->next;
	}
	return (tab);
}
