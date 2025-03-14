/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 13:26:01 by agruet            #+#    #+#             */
/*   Updated: 2025/03/14 16:45:48 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	assign_kv(char *var, t_map *map)
{
	char	*chr;

	chr = ft_strchr(var, '=');
	if (!chr)
		return (0);
	map->key = ft_substr(var, 0, chr - var);
	if (!map->key)
		return (0);
	map->value = ft_substr(var, chr - var + 1, ft_strlen(var));
	if (!map->value)
		return (free(map->key), 0);
	return (1);
}

static t_map	*create_first_var(void)
{
	t_map	*first_var;
	char	*key;
	char	*value;

	key = ft_strdup("?");
	if (!key)
		return (NULL);
	value = ft_strdup("0");
	if (!value)
		return (free(key), NULL);
	first_var = newmap(key, value);
	if (!first_var)
		return (free(key), free(value), NULL);
	return (first_var);
}

int	create_env(t_shell *minishell)
{
	size_t	i;
	t_map	*current;
	t_map	*previous;

	minishell->env = create_first_var();
	if (!minishell->env)
		return (0);
	i = 0;
	previous = minishell->env;
	while (__environ[i])
	{
		current = newmap(NULL, NULL);
		if (!current)
			return (ft_mapclear(&minishell->env), 0);
		if (!assign_kv(__environ[i], current))
			return (free(current), ft_mapclear(&minishell->env), 0);
		ft_addmap(&previous, current);
		previous = current;
		i++;
	}
	return (1);
}
