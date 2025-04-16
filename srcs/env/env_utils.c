/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:51:52 by agruet            #+#    #+#             */
/*   Updated: 2025/04/16 12:11:43 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_map	*get_env(t_map *env, const char *var, size_t len)
{
	t_map	*current;

	current = env;
	while (current)
	{
		if (!ft_strncmp(current->key, var,
				ft_max(len, ft_strlen(current->key))))
		{
			if (current->key[len] == 0)
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}

char	*get_env_value(t_map *env, const char *var, size_t len)
{
	t_map	*res;

	res = get_env(env, var, len);
	if (res == NULL || res->value == NULL)
		return ("");
	else
		return (res->value);
}

char	**convert_env(t_map *env)
{
	size_t	size;
	size_t	i;
	char	**tab;
	char	*temp;

	size = ft_mapsize(env);
	tab = ft_calloc(size + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		temp = ft_strjoin(env->key, "=");
		if (!temp)
			return (free_tab(tab, i), NULL);
		tab[i] = ft_strjoin(temp, env->value);
		free(temp);
		if (!tab[i])
			return (free_tab(tab, i), NULL);
		i++;
		env = env->next;
	}
	return (tab);
}
