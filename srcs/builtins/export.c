/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agruet <agruet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 11:17:55 by agruet            #+#    #+#             */
/*   Updated: 2025/02/26 14:58:46 by agruet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(t_mini *minishell, char *var)
{
	t_map	*new;
	t_map	*find;
	char	*chr;

	find = get_env(minishell, var);
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
		chr = ft_strchr(var, '=');
		if (!chr)
			return (1);
		find->value = ft_substr(var, chr - var + 1, ft_strlen(var));
		if (!find->value)
			return (1);
	}
	return (0);
}
