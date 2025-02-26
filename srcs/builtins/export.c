/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:17:55 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 15:05:10 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_mini *minishell, char *var)
{
	t_map	*new;
	t_map	*find;
	char	*chr;

	chr = ft_strchr(var, '=');
	if (!chr)
		return (1);
	find = get_env(minishell, var, chr - var);
	if (!find)
	{
		new = newmap(NULL, NULL);
		if (!new)
			return (1);
		if (!assign_kv(var, new))
			return (free(new), 1);
		ft_addmap(&minishell->env, new);
	}
	else
	{
		free(find->value);
		find->value = ft_substr(var, chr - var + 1, ft_strlen(var));
		if (!find->value)
			return (1);
	}
	return (0);
}
